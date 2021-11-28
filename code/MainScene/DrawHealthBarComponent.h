#pragma once
#include "MainSceneDrawComponent.h"

#include "Math.h"
#include "../Engine/Game.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "../Helper/HDrawLineFrame.h"

class EnemyHealthComponent;

namespace {
    struct Vertex {
    public:
        XMFLOAT3 position_;
        XMFLOAT2 texcoord_;
    };
    struct InfoToShader {
    public:
        XMMATRIX expand_;
        XMMATRIX translate_;
        XMMATRIX ortho_;
        float r_;
    };
}

/// <summary>
/// 敵機あるいは画面上部にヘルスバーを表示させるcomponent
/// </summary>
template<class T>
class DrawHealthBarComponent :
    public MainSceneDrawComponent
{
public:
    /// <param name="health">対象敵機の体力管理component double GetHealthRate()がメンバとして必要</param>
    /// <param name="offset">このコンポーネントの親オブジェクト座標から見てどの位置にヘルスバー中心を置くか</param>
    /// <param name="width">ヘルスバー幅</param>
    /// <param name="height">ヘルスバー高さ</param>
    DrawHealthBarComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, ComponentHandle<T> health, MatVec::Vector2 offset, double width = 30.0, double height = 6.0)
    : MainSceneDrawComponent(object, layer_manager, -7.5),
        center_offset_(offset), width_(width), height_(height), const_buffer_map_(nullptr), frame_(object->mScene->mGame), health_component_(health)
    {
        Game& game = mObj->mScene->mGame;
        if (pipeline_ == nullptr)
        {
            StaticGraphicInit(game);
        }
        NonstaticGraphicInit(game);
    }
    void Draw() override
    {
        InfoToShader* map = static_cast<InfoToShader*>(const_buffer_map_);
        map->expand_ = MatVec::ConvertToXMMATRIX(MatVec::Expand(width_, height_, 1.0));
        MatVec::Vector2 center = mObj->GetPosition() + center_offset_;
        map->translate_ = MatVec::ConvertToXMMATRIX(MatVec::Translation(center(0), center(1), 0.0));
        map->ortho_ = MatVec::ConvertToXMMATRIX(MatVec::GetOrthoGraphicProjection(600, 900, 0.0, 1.0));
        map->r_ = static_cast<float>(health_component_->GetHealthRate());

        Game& game = mObj->mScene->mGame;
        game.mdx12.SetGraphicsPipeline(pipeline_);
        game.mdx12.SetRootSignature(root_signature_);
        game.mdx12.SetDescriptorHeap(crv_heap_);
        game.mdx12.SetGraphicsRootDescriptorTable(0, crv_heap_, 0);
        game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLELIST);
        game.mdx12.SetVertexBuffers(vertex_buffer_, 0, sizeof(Vertex) * 4, sizeof(Vertex));
        game.mdx12.SetIndexBuffers(index_buffer_, 6);
        game.mdx12.SetViewports(600, 900, 0, 0, 1.0f, 0.0f);
        game.mdx12.SetScissorrect(0, 900, 0, 600);
        game.mdx12.DrawIndexedInstanced(6, 1, 0, 0, 0);

        frame_.DrawFrame(game, center(0), center(1), width_, height_, 0.0, 600, 900, MatVec::Vector4(0.0, 1.0, 0.0, 0.5));
    }
    ~DrawHealthBarComponent()
    {
    }
    //health_component_の親オブジェクト座標から見てどの位置にヘルスバー中心を置くか
    MatVec::Vector2 center_offset_;
    //ヘルスバー幅
    double width_;
    //ヘルスバー高さ
    double height_;
private:
    ComponentHandle<T> health_component_;
    static void StaticGraphicInit(Game& game)
    {
        auto vertex_shader = game.mShaderManager.GetDX12ShaderObject(14);
        auto pixel_shader = game.mShaderManager.GetDX12ShaderObject(15);

        DX12VertexLayout vertex_layout;
        vertex_layout.push_back(DX12VertexLayoutUnit(
            "POSITION", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
        ));
        vertex_layout.push_back(DX12VertexLayoutUnit(
            "TEXCOORD", DX12Config::VertexLayoutFormat::R32G32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
        ));

        DX12RootParameter root_param;
        root_param.mDescRanges.push_back(DX12DescriptorRange(
            1, DX12Config::DescriptorRangeType::CBV, 0, 0
        ));
        root_param.mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;

        root_signature_ = game.mdx12.CreateRootSignature(root_param, false);

        pipeline_ = game.mdx12.CreateGraphicsPipeline(
            vertex_shader, pixel_shader, vertex_layout, DX12Config::PrimitiveTopologyType::TRIANGLE, 1, root_signature_, L"DrawHealthBarComponent::pipeline_"
        );

        vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(Vertex) * 4, L"DrawHealthBarComponent::vertex_buffer_");
        Vertex vertex_array[4];
        //0 3
        //1 2
        vertex_array[0].position_ = XMFLOAT3(-0.5f, +0.5f, 0.0f);
        vertex_array[1].position_ = XMFLOAT3(-0.5f, -0.5f, 0.0f);
        vertex_array[2].position_ = XMFLOAT3(+0.5f, -0.5f, 0.0f);
        vertex_array[3].position_ = XMFLOAT3(+0.5f, +0.5f, 0.0f);
        vertex_array[0].texcoord_ = XMFLOAT2(0.0f, 0.0f);
        vertex_array[1].texcoord_ = XMFLOAT2(0.0f, 1.0f);
        vertex_array[2].texcoord_ = XMFLOAT2(1.0f, 1.0f);
        vertex_array[3].texcoord_ = XMFLOAT2(1.0f, 0.0f);
        Vertex* vertex_map = static_cast<Vertex*>(game.mdx12.Map(vertex_buffer_));
        std::memcpy(vertex_map, vertex_array, sizeof(vertex_array));
        game.mdx12.Unmap(vertex_buffer_);

        index_buffer_ = game.mdx12.CreateIndexBuffer(6, L"DrawHealthBarComponent::index_buffer_");
        unsigned int* index_map = static_cast<unsigned int*>(game.mdx12.Map(index_buffer_));
        index_map[0] = 0;
        index_map[1] = 1;
        index_map[2] = 3;
        index_map[3] = 1;
        index_map[4] = 2;
        index_map[5] = 3;
        game.mdx12.Unmap(index_buffer_);
    }
    void NonstaticGraphicInit(Game& game)
    {
        const_buffer_ = game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD, sizeof(InfoToShader), L"DrawHealthBarComponent::const_buffer_");
        crv_heap_ = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 1, L"DrawHealthBarComponent::crv_heap_");
        game.mdx12.CreateConstBufferView(const_buffer_, crv_heap_, 0);
        const_buffer_map_ = game.mdx12.Map(const_buffer_);
    }
    static boost::shared_ptr<DX12GraphicsPipeline> pipeline_;
    static boost::shared_ptr<DX12RootSignature> root_signature_;
    static boost::shared_ptr<DX12Resource> vertex_buffer_;
    static boost::shared_ptr<DX12Resource> index_buffer_;
    boost::shared_ptr<DX12Resource> const_buffer_;
    boost::shared_ptr<DX12DescriptorHeap> crv_heap_;
    void* const_buffer_map_;
    Helpers::HDrawLineFrame frame_;
};

template<class T>
boost::shared_ptr<DX12GraphicsPipeline> DrawHealthBarComponent<T>::pipeline_ = nullptr;
template<class T>
boost::shared_ptr<DX12RootSignature> DrawHealthBarComponent<T>::root_signature_ = nullptr;
template<class T>
boost::shared_ptr<DX12Resource> DrawHealthBarComponent<T>::vertex_buffer_ = nullptr;
template<class T>
boost::shared_ptr<DX12Resource> DrawHealthBarComponent<T>::index_buffer_ = nullptr;
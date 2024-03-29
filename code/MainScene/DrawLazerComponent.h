#pragma once
#include "MainSceneDrawComponent.h"

#include "Math.h"
#include "../Engine/Game.h"

/// <summary>
/// 両端が半円になっているレーザーの描画
/// </summary>
class DrawLazerComponent :
    public MainSceneDrawComponent
{
public:
    DrawLazerComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, double z);
    ~DrawLazerComponent();
    void Draw() override;
    //半円の半径
    double r_;
    //線分の両端(600*900座標)
    MatVec::Vector2 a_, b_;
private:
    static boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
    static boost::shared_ptr<DX12RootSignature> root_signature_;
    static boost::shared_ptr<DX12Resource> index_buffer_;
    static boost::shared_ptr<DX12Resource> vertex_buffer_;
    boost::shared_ptr<DX12DescriptorHeap> desc_heap_;
    boost::shared_ptr<DX12Resource> const_buffer_;
    void* const_buffer_map_;
    static void StaticGraphicInit(Game& game);
    void NonstaticGraphicInit(Game& game);
};


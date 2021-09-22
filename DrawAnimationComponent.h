#pragma once
#include "MainSceneDrawComponent.h"

#include "Math.h"
#include "Game.h"

/// <summary>
/// アニメーションを描画する
/// </summary>
class DrawAnimationComponent :
    public MainSceneDrawComponent
{
public:
    /// <param name="texture_id">アニメーションの各フレームの絵が整列した1枚のテクスチャのID</param>
    /// <param name="flame_width">1フレームの絵の幅[px]</param>
    /// <param name="flame_height">1フレームの絵の高さ[px]</param>
    /// <param name="column">元テクスチャが何列に渡りコマを含むか</param>
    /// <param name="row">元テクスチャが何行に渡りコマを含むか</param>
    /// <param name="offset">画像の描画中心位置の，親オブジェクト位置からのずれ</param>
    /// <param name="flame_num">1ループが何フレームか</param>
    DrawAnimationComponent(GameObjectHandle obj, boost::shared_ptr<LayerManager> layer_manager, unsigned int texture_id, double flame_width, double flame_height, unsigned int column, unsigned int row, double z, MatVec::Vector2 offset, unsigned int flame_num);
    ~DrawAnimationComponent();
    void Draw() override;
    MatVec::Vector2 center_offset_;
    //UpdateComponentから++するようにしないと，ポーズ時などに再生が停止しない
    int counter_;
private:
    //1フレーム分の絵の幅，高さ
    double flame_width_;
    double flame_height_;
    unsigned int column_;
    unsigned int row_;
    unsigned int flame_num_;
    static boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
    static boost::shared_ptr<DX12RootSignature> root_signature_;
    static boost::shared_ptr<DX12Resource> index_buffer_;
    static boost::shared_ptr<DX12Resource> vertex_buffer_;
    boost::shared_ptr<DX12DescriptorHeap> desc_heap_;
    boost::shared_ptr<DX12Resource> const_buffer_;
    void* const_buffer_map_;
    static void StaticGraphicInit(Game& game);
    void NonstaticGraphicInit(Game& game, unsigned int texture_id);
};


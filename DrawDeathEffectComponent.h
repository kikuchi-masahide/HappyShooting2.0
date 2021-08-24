#pragma once
#include "MainSceneDrawComponent.h"

#include "Game.h"
#include "GameObject.h"

/// <summary>
/// 死亡エフェクトを描画
/// 描画が終わったらオブジェクトを殺すか否かを選択できる
/// </summary>
class DrawDeathEffectComponent :
    public MainSceneDrawComponent
{
public:
    /// <param name="z">描画z(省略時20)</param>
    /// <param name="radius">半径[px](省略時50)</param>
    /// <param name="will_kill_object">描画終了時オブジェクトと心中するか否か(省略でtrue)</param>
    /// <param name="offset">円中心の，親オブジェクト位置からのオフセット(省略時(0,0))</param>
    DrawDeathEffectComponent(GameObjectHandle obj, boost::shared_ptr<LayerManager> layer_manager, double z = 20, double max_radius = 50.0, bool will_kill_object = true, MatVec::Vector2 offset = MatVec::Vector2(0,0));
    ~DrawDeathEffectComponent();
    void Draw() override;
private:
    static boost::shared_ptr<DX12GraphicsPipeline> pipeline_;
    static boost::shared_ptr<DX12RootSignature> root_signature_;
    static boost::shared_ptr<DX12Resource> vertex_buffer_;
    static boost::shared_ptr<DX12Resource> index_buffer_;
    boost::shared_ptr<DX12Resource> const_buffer_;
    boost::shared_ptr<DX12DescriptorHeap> crv_heap_;
    static void StaticGraphicInit(Game& game);
    void NonstaticGraphicInit(Game& game);
    double max_radius_;
    bool will_kill_object_;
    MatVec::Vector2 offset_;
    void* const_buffer_map_;
    unsigned int time_;
};


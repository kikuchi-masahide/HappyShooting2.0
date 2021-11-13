#pragma once
#include "MainSceneBaseLayer.h"

#include "../Engine/Game.h"
#include "../Helper/HDrawLineFrame.h"

class MainSceneClippingLayer :
    public MainSceneBaseLayer
{
public:
    MainSceneClippingLayer(Scene* scene, DrawComponentsMultiset* draw_components, GameObjectHandle myself);
    ~MainSceneClippingLayer();
    void UniqueDraw() override;
    MatVec::Matrix4x4 GetLayerTransform() override;
private:
    //‰½tick‚ÌŠÔ‰~‚ğûk‚³‚¹CƒNƒŠƒbƒv‚ğˆÛ‚µCŒ³‚Ìó‘Ô‚É–ß‚·‚©
    static constexpr unsigned int shrinking_period_ = 120;
    static constexpr unsigned int maintain_period_ = 60 * 20;
    static constexpr unsigned int clearing_period_ = 120;
    //”¼Œa‚ğ‰½‚Ü‚Åk‚ß‚é‚©
    static constexpr double min_r_ = 60.0;
    boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
    boost::shared_ptr<DX12RootSignature> root_signature_;
    boost::shared_ptr<DX12DescriptorHeap> desc_heap_;
    boost::shared_ptr<DX12Resource> const_buffer_;
    boost::shared_ptr<DX12Resource> vertex_buffer_;
    boost::shared_ptr<DX12Resource> index_buffer_;
    void GraphicInit();
    GameObjectHandle myself_;
    Helpers::HDrawLineFrame frame_;
};


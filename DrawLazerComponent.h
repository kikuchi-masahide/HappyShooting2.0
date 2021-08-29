#pragma once
#include "MainSceneDrawComponent.h"

#include "Math.h"
#include "Game.h"

/// <summary>
/// —¼’[‚ª”¼‰~‚É‚È‚Á‚Ä‚¢‚éƒŒ[ƒU[‚Ì•`‰æ
/// </summary>
class DrawLazerComponent :
    public MainSceneDrawComponent
{
public:
    DrawLazerComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, double z);
    ~DrawLazerComponent();
    void Draw() override;
    //”¼‰~‚Ì”¼Œa
    double r_;
    //ü•ª‚Ì—¼’[(600*900À•W)
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


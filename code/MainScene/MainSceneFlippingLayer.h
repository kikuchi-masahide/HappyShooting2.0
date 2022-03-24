#pragma once
#include "MainSceneBaseLayer.h"

class MainSceneFlippingLayer :
    public MainSceneBaseLayer
{
public:
    MainSceneFlippingLayer(Scene* scene, DrawComponentsMultiset* draw_components);
    ~MainSceneFlippingLayer();
    void UniqueDraw() override;
    MatVec::Matrix4x4 GetLayerTransform() override;
private:
    void GraphicsInit(Game& game);
    //‚»‚Ì‚Ü‚Ü‚ÌF‚Å•`‰æ‚·‚é(•\‘¤—p)
    boost::shared_ptr<DX12GraphicsPipeline> pipeline_front_;
    boost::shared_ptr<DX12RootSignature> root_signature_front_;
    //F‚ğ”½“]‚³‚¹‚Ä•`‰æ‚·‚é(— ‘¤—p)
    boost::shared_ptr<DX12GraphicsPipeline> pipeline_back_;
    boost::shared_ptr<DX12RootSignature> root_signature_back_;
    boost::shared_ptr<DX12Resource> vertex_buffer_;
    boost::shared_ptr<DX12Resource> index_buffer_;
    void* vertex_map_;
    //˜gü—p
    boost::shared_ptr<DX12GraphicsPipeline> pipeline_frame_;
    boost::shared_ptr<DX12RootSignature> root_signature_frame_;
    //”Â‚Ì‰ñ“]Šp“xtheta(0 <= theta < 2PI)‚ğ•Ô‚·
    double GetRotation();
    //”Â‚ğ”¼‰ñ“]‚³‚¹‚é‚Ì‚É‚©‚¯‚étick”
    static const int halfturn_time_;
    //”Â‚ğ‰ñ“]‚³‚¹‚¸‚Æ‚Ç‚ß‚éŠÔ
    static const int stay_time_;
    //‰½‰ñ”¼‰ñ“]‚ğs‚¤‚©
    static const int halfturn_num_;
};


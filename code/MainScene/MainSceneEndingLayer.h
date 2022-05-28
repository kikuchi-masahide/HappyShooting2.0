#pragma once
#include "MainSceneBaseLayer.h"

#include "../Helper/HDrawLineFrame.h"

class MainSceneEndingLayer :
    public MainSceneBaseLayer
{
public:
    MainSceneEndingLayer(Scene* scene, DrawComponentsMultiset* draw_components);
    ~MainSceneEndingLayer();
    void UniqueDraw() override;
private:
    void GraphicInit(Game& game);
    boost::shared_ptr<DX12GraphicsPipeline> pipeline_;
    boost::shared_ptr<DX12RootSignature> rootsignature_;
    boost::shared_ptr<DX12DescriptorHeap> heap_;
    boost::shared_ptr<DX12Resource> vertex_;
    boost::shared_ptr<DX12Resource> index_;
    boost::shared_ptr<DX12Resource> const_;
    Helpers::HDrawLineFrame frame_;
};


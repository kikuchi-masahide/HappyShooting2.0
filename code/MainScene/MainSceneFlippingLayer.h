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
    //そのままの色で描画する(表側用)
    boost::shared_ptr<DX12GraphicsPipeline> pipeline_front_;
    boost::shared_ptr<DX12RootSignature> root_signature_front_;
    //色を反転させて描画する(裏側用)
    boost::shared_ptr<DX12GraphicsPipeline> pipeline_back_;
    boost::shared_ptr<DX12RootSignature> root_signature_back_;
    boost::shared_ptr<DX12Resource> vertex_buffer_;
    boost::shared_ptr<DX12Resource> index_buffer_;
    void* vertex_map_;
    //枠線用
    boost::shared_ptr<DX12GraphicsPipeline> pipeline_frame_;
    boost::shared_ptr<DX12RootSignature> root_signature_frame_;
    //板の回転角度theta(0 <= theta < 2PI)を返す
    double GetRotation();
    //板を半回転させるのにかけるtick数
    static const int halfturn_time_;
    //板を回転させずとどめる時間
    static const int stay_time_;
    //何回半回転を行うか
    static const int halfturn_num_;
};


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
    //���̂܂܂̐F�ŕ`�悷��(�\���p)
    boost::shared_ptr<DX12GraphicsPipeline> pipeline_front_;
    boost::shared_ptr<DX12RootSignature> root_signature_front_;
    //�F�𔽓]�����ĕ`�悷��(�����p)
    boost::shared_ptr<DX12GraphicsPipeline> pipeline_back_;
    boost::shared_ptr<DX12RootSignature> root_signature_back_;
    boost::shared_ptr<DX12Resource> vertex_buffer_;
    boost::shared_ptr<DX12Resource> index_buffer_;
    void* vertex_map_;
    //�g���p
    boost::shared_ptr<DX12GraphicsPipeline> pipeline_frame_;
    boost::shared_ptr<DX12RootSignature> root_signature_frame_;
    //�̉�]�p�xtheta(0 <= theta < 2PI)��Ԃ�
    double GetRotation();
    //�𔼉�]������̂ɂ�����tick��
    static const int halfturn_time_;
    //����]�������Ƃǂ߂鎞��
    static const int stay_time_;
    //���񔼉�]���s����
    static const int halfturn_num_;
};


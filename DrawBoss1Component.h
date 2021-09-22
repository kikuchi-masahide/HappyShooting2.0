#pragma once
#include "MainSceneDrawComponent.h"

#include "GameObjectHandle.h"
#include "Game.h"
#include "Math.h"

class DrawBoss1Component :
    public MainSceneDrawComponent
{
public:
    DrawBoss1Component(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, double z);
    ~DrawBoss1Component();
    void Draw() override;
    //Update����Component����ύX����
    int t_;
private:
    //�l�p�`���ЂƂÂ`�ʂ���D�v4����s
    boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
    boost::shared_ptr<DX12RootSignature> root_signature_;
    boost::shared_ptr<DX12Resource> vertex_buffer_;
    //4�̎l�p�`��`�悷��̂�4�̒萔�o�b�t�@���g��
    boost::shared_ptr<DX12Resource> const_buffer_[4];
    boost::shared_ptr<DX12DescriptorHeap> desc_heap_[4];
    void* const_map_[4];
    void GraphicsInit();
    //�l�p�`1�̕�
    static constexpr double square_w_ = 100.0;
    //1tick�̉�]�p�x
    static constexpr double delta_theta_ = PI / 120;
};


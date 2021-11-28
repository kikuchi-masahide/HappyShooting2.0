#pragma once
#include "MainSceneBaseLayer.h"

#include "../Engine/Game.h"
#include "../Helper/HDrawLineFrame.h"

//�����`�̘g����]�C�k�����ĕ`��̈�����肷��(Boss1State3)
class MainSceneShrinkLayer :
    public MainSceneBaseLayer
{
public:
    MainSceneShrinkLayer(Scene* scene, DrawComponentsMultiset* draw_components);
    ~MainSceneShrinkLayer();
    void UniqueDraw() override;
    MatVec::Matrix4x4 GetLayerTransform() override;
private:
	void GraphicsInit(Game& game);
	//counter_�����̒l�ɂȂ�Update�܂Ŏ��s����
	static constexpr int whole_period_ = 780 - 1;
	//���@�ړ��̈�k���C�Ċg��ɉ�tick�����邩
	static constexpr unsigned int shrink_period_ = 240;
	//���̊p�x�܂ňړ��̈���X����
	static constexpr double max_rotate_angle_ = -PI / 3;
	//�ړ��̈�����{�Ɋg�傷�邩
	static constexpr double max_expand_ratio_ = 0.4;
	boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
	boost::shared_ptr<DX12RootSignature> root_signature_;
	boost::shared_ptr<DX12Resource> vertex_buffer_;
	boost::shared_ptr<DX12Resource> index_buffer_;
	boost::shared_ptr<DX12Resource> const_buffer_;
	boost::shared_ptr<DX12DescriptorHeap> desc_heap_;
	void* const_buffer_map_;
	Helpers::HDrawLineFrame frame_;
};


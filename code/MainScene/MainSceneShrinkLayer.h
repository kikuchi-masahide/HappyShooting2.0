#pragma once
#include "MainSceneBaseLayer.h"

#include "../Engine/Game.h"
#include "../Helper/HDrawLineFrame.h"

//’·•ûŒ`‚Ì˜g‚ğ‰ñ“]Ck¬‚µ‚Ä•`‰æ—Ìˆæ‚ğŒÀ’è‚·‚é(Boss1State3)
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
	//counter_‚ª‚±‚Ì’l‚É‚È‚éUpdate‚Ü‚ÅÀs‚·‚é
	static constexpr int whole_period_ = 780 - 1;
	//©‹@ˆÚ“®—Ìˆæk¬CÄŠg‘å‚É‰½tick‚©‚¯‚é‚©
	static constexpr unsigned int shrink_period_ = 240;
	//‚±‚ÌŠp“x‚Ü‚ÅˆÚ“®—Ìˆæ‚ğŒX‚¯‚é
	static constexpr double max_rotate_angle_ = -PI / 3;
	//ˆÚ“®—Ìˆæ‚ğ‰½”{‚ÉŠg‘å‚·‚é‚©
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


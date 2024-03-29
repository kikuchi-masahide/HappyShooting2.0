#pragma once
#include "MainSceneBaseLayer.h"

#include "../Engine/Game.h"
#include "../Helper/HDrawLineFrame.h"

//長方形の枠を回転，縮小して描画領域を限定する(Boss1State3)
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
	//counter_がこの値になるUpdateまで実行する
	static constexpr int whole_period_ = 780 - 1;
	//自機移動領域縮小，再拡大に何tickかけるか
	static constexpr unsigned int shrink_period_ = 240;
	//この角度まで移動領域を傾ける
	static constexpr double max_rotate_angle_ = -PI / 3;
	//移動領域を何倍に拡大するか
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


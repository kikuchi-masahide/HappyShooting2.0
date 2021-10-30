#pragma once
#include "../Engine/Game.h"

//画面一面にベタ塗するヘルパ(同tickに複数実行することは想定していないのでstaticとしている)
class HBetapaint
{
public:
	static void Beta(Game& game, MatVec::Vector4 rgba);
private:
	static boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
	static boost::shared_ptr<DX12RootSignature> root_signature_;
	static boost::shared_ptr<DX12DescriptorHeap> desc_heap_;
	static boost::shared_ptr<DX12Resource> vertex_buffer_;
	static boost::shared_ptr<DX12Resource> index_buffer_;
	static boost::shared_ptr<DX12Resource> const_buffer_;
	static void GraphicsInit(Game& game);
	static void* const_map_;
};


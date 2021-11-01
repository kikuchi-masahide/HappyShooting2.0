#include "HBetapaint.h"

#include "../Engine/window.h"

namespace {
	struct InfoToShader {
	public:
		XMFLOAT3 rgb_;
		float alpha_;
	};
}

void HBetapaint::Beta(Game& game, MatVec::Vector4 rgba)
{
	if (graphics_pipeline_ == nullptr)
	{
		GraphicsInit(game);
	}
	InfoToShader* const_map = static_cast<InfoToShader*>(const_map_);
	const_map->rgb_ = XMFLOAT3(rgba(0), rgba(1), rgba(2));
	const_map->alpha_ = rgba(3);

	game.mdx12.SetGraphicsPipeline(graphics_pipeline_);
	game.mdx12.SetRootSignature(root_signature_);
	game.mdx12.SetDescriptorHeap(desc_heap_);
	game.mdx12.SetGraphicsRootDescriptorTable(0, desc_heap_, 0);
	game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLELIST);
	game.mdx12.SetVertexBuffers(vertex_buffer_,0,sizeof(XMFLOAT3)*4,sizeof(XMFLOAT3));
	game.mdx12.SetIndexBuffers(index_buffer_, 6);
	game.mdx12.SetViewports(900, 900, 0, 0, 0.0f, 1.0f);
	game.mdx12.SetScissorrect(0.0f, 900.0f, 0.0f, 900.0f);
	game.mdx12.DrawIndexedInstanced(6, 1, 0, 0, 0);
}

void HBetapaint::GraphicsInit(Game& game)
{
	auto vertex = game.mShaderManager.GetDX12ShaderObject(20);
	auto pixel = game.mShaderManager.GetDX12ShaderObject(21);

	DX12VertexLayout vertex_layout;
	vertex_layout.push_back(DX12VertexLayoutUnit(
		"POSITION", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));

	DX12RootParameter root_param;
	root_param.mDescRanges.push_back(DX12DescriptorRange(
		1, DX12Config::DescriptorRangeType::CBV, 0, 0
	));
	root_param.mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;
	root_signature_ = game.mdx12.CreateRootSignature(root_param,false);

	graphics_pipeline_ = game.mdx12.CreateGraphicsPipeline(
		vertex, pixel, vertex_layout, DX12Config::PrimitiveTopologyType::TRIANGLE, 1, root_signature_,L"HBetapaint::graphics_pipeline_"
	);

	vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(XMFLOAT3) * 4, L"HBetapaint::vertex_buffer_");
	XMFLOAT3* vertex_map = static_cast<XMFLOAT3*>(game.mdx12.Map(vertex_buffer_));
	vertex_map[0] = XMFLOAT3(-1.0f, +1.0f, 0.0f);
	vertex_map[1] = XMFLOAT3(-1.0f, -1.0f, 0.0f);
	vertex_map[2] = XMFLOAT3(+1.0f, -1.0f, 0.0f);
	vertex_map[3] = XMFLOAT3(+1.0f, +1.0f, 0.0f);
	game.mdx12.Unmap(vertex_buffer_);

	index_buffer_ = game.mdx12.CreateIndexBuffer(6, L"HBetapaint::index_buffer_");
	unsigned int* index_map = static_cast<unsigned int*>(game.mdx12.Map(index_buffer_));
	index_map[0] = 0;
	index_map[1] = 1;
	index_map[2] = 3;
	index_map[3] = 1;
	index_map[4] = 2;
	index_map[5] = 3;
	game.mdx12.Unmap(index_buffer_);

	const_buffer_ = game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD, sizeof(InfoToShader), L"HBetapaint::const_buffer_");
	const_map_ = game.mdx12.Map(const_buffer_);

	desc_heap_ = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 1, L"HBetapaint::desc_heap_");
	game.mdx12.CreateConstBufferView(const_buffer_, desc_heap_, 0);
}

boost::shared_ptr<DX12GraphicsPipeline> HBetapaint::graphics_pipeline_ = nullptr;
boost::shared_ptr<DX12RootSignature> HBetapaint::root_signature_ = nullptr;
boost::shared_ptr<DX12DescriptorHeap> HBetapaint::desc_heap_ = nullptr;
boost::shared_ptr<DX12Resource> HBetapaint::vertex_buffer_ = nullptr;
boost::shared_ptr<DX12Resource> HBetapaint::index_buffer_ = nullptr;
boost::shared_ptr<DX12Resource> HBetapaint::const_buffer_ = nullptr;
void* HBetapaint::const_map_ = nullptr;
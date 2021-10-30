#include "stdafx.h"
#include "PolygonGeometryDrawer.h"

#include "PolygonGeometry.h"

PolygonGeometryDrawer::PolygonGeometryDrawer(PolygonGeometry* polygon, MatVec::Vector3 color, Game& game)
	:polygon_(polygon),color_(color),vertex_map_(nullptr),v_(polygon->points_.size()),frame_(game)
{
	if (graphics_pipeline_ == nullptr)
	{
		StaticGraphicInit(game);
	}
	NonstaticGraphicInit(game);
}

PolygonGeometryDrawer::~PolygonGeometryDrawer()
{
}

void PolygonGeometryDrawer::Update()
{
	for (int n = 0; n < v_; n++)
	{
		vertex_map_[n] = MatVec::ConvertToXMFLOAT3(MatVec::XY0(polygon_->points_[n]));
	}
}

void PolygonGeometryDrawer::Output(Game& game)
{
	game.mdx12.SetGraphicsPipeline(graphics_pipeline_);
	game.mdx12.SetRootSignature(root_signature_);
	game.mdx12.SetDescriptorHeap(desc_heap_);
	game.mdx12.SetGraphicsRootDescriptorTable(0, desc_heap_, 0);
	game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLELIST);
	game.mdx12.SetVertexBuffers(vertex_buffer_,0,sizeof(XMFLOAT3)*v_,sizeof(XMFLOAT3));
	game.mdx12.SetIndexBuffers(index_buffer_,3*(v_-2));
	game.mdx12.SetViewports(900, 900, 0, 0, 0.0f, 1.0f);
	game.mdx12.SetScissorrect(0.0f, 900.0f, 0.0f, 900.0f);
	game.mdx12.DrawIndexedInstanced(3 * (v_ - 2), 1, 0, 0, 0);
	Rect2 aabb = polygon_->GetAABB();
	auto center = aabb.GetCenter();
	center += MatVec::Vector2(-150.0, 0.0);
	frame_.DrawFrame(game, center(0), center(1), aabb.GetWidth(), aabb.GetHeight(), 0.0, 900.0, 900.0, MatVec::XYZ1(color_));
}

void PolygonGeometryDrawer::StaticGraphicInit(Game& game)
{
	auto vertex = game.mShaderManager.GetDX12ShaderObject(22);
	auto pixel = game.mShaderManager.GetDX12ShaderObject(23);

	DX12VertexLayout vertex_layout;
	vertex_layout.push_back(DX12VertexLayoutUnit(
		"POSITION", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));

	DX12RootParameter root_param;
	root_param.mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;
	root_param.mDescRanges.push_back(DX12DescriptorRange(
		2, DX12Config::DescriptorRangeType::CBV, 0, 0
	));
	root_signature_ = game.mdx12.CreateRootSignature(root_param, false);

	graphics_pipeline_ = game.mdx12.CreateGraphicsPipeline(
		vertex, pixel, vertex_layout, DX12Config::PrimitiveTopologyType::TRIANGLE, 1, root_signature_, L"PolygonGeometryDrawer::graphics_pipeline_"
	);

	matrix_buffer_ = game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD, sizeof(XMMATRIX), L"PolygonGeometryDrawer::matrix_buffer_");
	XMMATRIX* matrix_map = static_cast<XMMATRIX*>(game.mdx12.Map(matrix_buffer_));
	*matrix_map = MatVec::ConvertToXMMATRIX(
		MatVec::GetOrthoGraphicProjection(900.0, 900.0, 0.0, 1.0) * MatVec::Translation(-150.0, 0.0, 0.0)
	);
	game.mdx12.Unmap(matrix_buffer_);
}

void PolygonGeometryDrawer::NonstaticGraphicInit(Game& game)
{
	color_buffer_ = game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD, sizeof(XMFLOAT3), L"PolygonGeometryDrawer::color_buffer_");
	XMFLOAT3* color_map_ = static_cast<XMFLOAT3*>(game.mdx12.Map(color_buffer_));
	*color_map_ = MatVec::ConvertToXMFLOAT3(color_);
	game.mdx12.Unmap(color_buffer_);
	desc_heap_ = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 2, L"PolygonGeometryDrawer::desc_heap_");
	game.mdx12.CreateConstBufferView(matrix_buffer_, desc_heap_, 0);
	game.mdx12.CreateConstBufferView(color_buffer_, desc_heap_, 1);

	vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(XMFLOAT3) * v_, L"PolygonGeometryDrawer::vertex_buffer_");
	vertex_map_ = static_cast<XMFLOAT3*>(game.mdx12.Map(vertex_buffer_));
	
	index_buffer_ = game.mdx12.CreateIndexBuffer(sizeof(unsigned int) * 3 * (v_ - 2), L"PolygonGeometryDrawer::index_buffer_");
	unsigned int* index_map = static_cast<unsigned int*>(game.mdx12.Map(index_buffer_));
	for (unsigned int i = 2; i < v_; i++)
	{
		index_map[3 * (i - 2) + 0] = 0;
		index_map[3 * (i - 2) + 1] = i - 1;
		index_map[3 * (i - 2) + 2] = i;
	}
	game.mdx12.Unmap(index_buffer_);
}

boost::shared_ptr<DX12GraphicsPipeline> PolygonGeometryDrawer::graphics_pipeline_ = nullptr;
boost::shared_ptr<DX12RootSignature> PolygonGeometryDrawer::root_signature_ = nullptr;
boost::shared_ptr<DX12Resource> PolygonGeometryDrawer::matrix_buffer_ = nullptr;

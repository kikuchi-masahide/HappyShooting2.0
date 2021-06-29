#include "stdafx.h"
#include "DrawNormalBulletComponent.h"

#include "MainScene.h"

DrawNormalBulletComponent::DrawNormalBulletComponent(MainScene* scene, GameObjectHandle object, double radius, MatVec::Vector3 edge_rgb, double edge_alpha)
	: MainSceneDrawComponent(scene), object_handle_(object), radius_(radius), edge_rgb_(edge_rgb),edge_alpha_(edge_alpha)
{
	if (graphics_pipeline_ == nullptr)
	{
		StaticGraphicalInit(scene_);
	}
	NonstaticGraphicalInit();
}

void DrawNormalBulletComponent::StaticGraphicalInit(MainScene* scene)
{
	Game& game = scene->mGame;
	
	auto vertex_shader = game.mShaderManager.GetDX12ShaderObject(8);
	auto pixel_shader = game.mShaderManager.GetDX12ShaderObject(9);

	DX12VertexLayout vertex_layout;
	vertex_layout.push_back(DX12VertexLayoutUnit(
		"POSITION", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));
	vertex_layout.push_back(DX12VertexLayoutUnit(
		"TEXCOORD", DX12Config::VertexLayoutFormat::R32G32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));

	std::vector<DX12RootParameter> root_params;
	root_params.push_back(DX12RootParameter());
	root_params.back().mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;
	root_params.back().mDescRanges.push_back(DX12DescriptorRange(
		1, DX12Config::DescriptorRangeType::CBV, 0, 0
	));
	root_signature_ = game.mdx12.CreateRootSignature(root_params);
	
	graphics_pipeline_ = game.mdx12.CreateGraphicsPipeline(
		vertex_shader,pixel_shader,vertex_layout,
		DX12Config::PrimitiveTopologyType::TRIANGLE,1,root_signature_
	);

	//0 3
	//1 2
	index_buffer_ = game.mdx12.CreateIndexBuffer(6);
	unsigned int* index_map = static_cast<unsigned int*>(game.mdx12.Map(index_buffer_));
	index_map[0] = 0;
	index_map[1] = 1;
	index_map[2] = 3;
	index_map[3] = 3;
	index_map[4] = 1;
	index_map[5] = 2;
	game.mdx12.Unmap(index_buffer_);
}

void DrawNormalBulletComponent::NonstaticGraphicalInit()
{
	Game& game = scene_->mGame;

	vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(float) * 20);
	Vertex vertexs[4] = {
		Vertex(MatVec::Vector2(0.0,0.0)),
		Vertex(MatVec::Vector2(0.0,1.0)),
		Vertex(MatVec::Vector2(1.0,1.0)),
		Vertex(MatVec::Vector2(1.0,0.0))
	};
	vertex_map_ = static_cast<float*>(game.mdx12.Map(vertex_buffer_));
	for (unsigned int n = 0; n < 4; n++)
	{
		vertex_map_[5 * n + 0] = vertexs[n].pos_(0);
		vertex_map_[5 * n + 1] = vertexs[n].pos_(1);
		vertex_map_[5 * n + 2] = vertexs[n].pos_(2);
		vertex_map_[5 * n + 3] = vertexs[n].uv_(0);
		vertex_map_[5 * n + 4] = vertexs[n].uv_(1);
	}

	crv_resource_ = game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD, sizeof(InfoToShader));
	crv_desc_heap_ = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 1);
	game.mdx12.CreateConstBufferView(crv_resource_, crv_desc_heap_, 0);
	crv_map_ = static_cast<InfoToShader*>(game.mdx12.Map(crv_resource_));
}

void DrawNormalBulletComponent::Draw()
{
	Game& game = scene_->mGame;

	//円の中心
	MatVec::Vector2 center = object_handle_->GetPosition() + center_offset_;
	//頂点4つ
	MatVec::Vector2 vertexs[4];
	vertexs[0] = center + MatVec::Vector2(-radius_, +radius_);
	vertexs[1] = center + MatVec::Vector2(-radius_, -radius_);
	vertexs[2] = center + MatVec::Vector2(+radius_, -radius_);
	vertexs[3] = center + MatVec::Vector2(+radius_, +radius_);
	//頂点バッファにマップ
	for (unsigned int n = 0; n < 4; n++)
	{
		vertexs[n](0) = 2 * vertexs[n](0) / 600 - 1;
		vertexs[n](1) = 2 * vertexs[n](1) / 900 - 1;
		vertex_map_[5 * n + 0] = vertexs[n](0);
		vertex_map_[5 * n + 1] = vertexs[n](1);
	}

	//定数バッファ
	InfoToShader info;
	info.r_ = edge_rgb_(0);
	info.g_ = edge_rgb_(1);
	info.b_ = edge_rgb_(2);
	info.alpha_ = edge_alpha_;
	*crv_map_ = info;

	//もろもろセット
	game.mdx12.SetGraphicsPipeline(graphics_pipeline_);
	game.mdx12.SetRootSignature(root_signature_);
	game.mdx12.SetDescriptorHeap(crv_desc_heap_);
	game.mdx12.SetGraphicsRootDescriptorTable(0, crv_desc_heap_, 0);
	game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLELIST);
	game.mdx12.SetVertexBuffers(vertex_buffer_, 0, sizeof(float) * 20, sizeof(float)*5);
	game.mdx12.SetIndexBuffers(index_buffer_,6);
	game.mdx12.SetViewports(600, 900, 0, 0, 1.0, 0.0);
	game.mdx12.SetScissorrect(0, 900, 0, 600);
	game.mdx12.DrawIndexedInstanced(6, 1, 0, 0, 0);
}

DrawNormalBulletComponent::~DrawNormalBulletComponent()
{
}

boost::shared_ptr<DX12GraphicsPipeline> DrawNormalBulletComponent::graphics_pipeline_ = nullptr;
boost::shared_ptr<DX12RootSignature> DrawNormalBulletComponent::root_signature_ = nullptr;
boost::shared_ptr<DX12Resource> DrawNormalBulletComponent::index_buffer_ = nullptr;
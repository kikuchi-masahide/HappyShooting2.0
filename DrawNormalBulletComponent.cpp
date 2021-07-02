#include "stdafx.h"
#include "DrawNormalBulletComponent.h"

#include "MainScene.h"

//実装のみに使う構造体
namespace{
	struct Vertex {
	public:
		XMFLOAT3 pos_;
		XMFLOAT2 uv_;
	};
	//シェーダに渡す情報
	struct InfoToShader {
	public:
		XMMATRIX mat_;
		XMFLOAT3 rgb_;
		float alpha_;
	};
}

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
		DX12Config::PrimitiveTopologyType::TRIANGLE,1,root_signature_,
		L"DrawNormalBulletComponent::graphics_pipeline_"
	);

	//0 3
	//1 2
	index_buffer_ = game.mdx12.CreateIndexBuffer(6, L"DrawNormalBulletComponent IndexBuffer");
	unsigned int* index_map = static_cast<unsigned int*>(game.mdx12.Map(index_buffer_));
	index_map[0] = 0;
	index_map[1] = 1;
	index_map[2] = 3;
	index_map[3] = 3;
	index_map[4] = 1;
	index_map[5] = 2;
	game.mdx12.Unmap(index_buffer_);

	//頂点バッファ
	vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(Vertex) * 4,L"DrawNormalBulletComponent VertexBuffer");
	Vertex vertexs[4];
	vertexs[0].uv_ = XMFLOAT2(0.0f, 0.0f);
	vertexs[1].uv_ = XMFLOAT2(0.0f, 1.0f);
	vertexs[2].uv_ = XMFLOAT2(1.0f, 1.0f);
	vertexs[3].uv_ = XMFLOAT2(1.0f, 0.0f);
	vertexs[0].pos_ = XMFLOAT3(-1.0f, +1.0f, 0.0f);
	vertexs[1].pos_ = XMFLOAT3(-1.0f, -1.0f, 0.0f);
	vertexs[2].pos_ = XMFLOAT3(+1.0f, -1.0f, 0.0f);
	vertexs[3].pos_ = XMFLOAT3(+1.0f, +1.0f, 0.0f);
	void* vertex_map = game.mdx12.Map(vertex_buffer_);
	std::memcpy(vertex_map, vertexs, sizeof(vertexs));
	game.mdx12.Unmap(vertex_buffer_);
}

void DrawNormalBulletComponent::NonstaticGraphicalInit()
{
	Game& game = scene_->mGame;

	crv_resource_ = game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD, sizeof(InfoToShader), L"DrawNormalBulletComponent Const Buffer");
	crv_desc_heap_ = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 1, L"DrawNormalBulletComponent::crv_desc_heap_");
	game.mdx12.CreateConstBufferView(crv_resource_, crv_desc_heap_, 0);
	crv_map_ = game.mdx12.Map(crv_resource_);
}

void DrawNormalBulletComponent::Draw()
{
	Game& game = scene_->mGame;

	//定数バッファ
	MatVec::Matrix4x4 matrix = MatVec::Expand(radius_, radius_, 1.0);
	//円の中心
	MatVec::Vector2 center = object_handle_->GetPosition() + center_offset_;
	matrix = MatVec::Translation(MatVec::XY0(center)) * matrix;
	matrix = MatVec::GetOrthoGraphicProjection(600, 900, 0.0, 1.0) * matrix;
	InfoToShader info;
	info.mat_ = MatVec::ConvertToXMMATRIX(matrix);
	info.rgb_ = MatVec::ConvertToXMFLOAT3(edge_rgb_);
	info.alpha_ = edge_alpha_;
	std::memcpy(crv_map_, &info, sizeof(InfoToShader));

	//もろもろセット
	game.mdx12.SetGraphicsPipeline(graphics_pipeline_);
	game.mdx12.SetRootSignature(root_signature_);
	game.mdx12.SetDescriptorHeap(crv_desc_heap_);
	game.mdx12.SetGraphicsRootDescriptorTable(0, crv_desc_heap_, 0);
	game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLELIST);
	game.mdx12.SetVertexBuffers(vertex_buffer_, 0, sizeof(Vertex) * 4, sizeof(Vertex));
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
boost::shared_ptr<DX12Resource> DrawNormalBulletComponent::vertex_buffer_ = nullptr;

#include "stdafx.h"
#include "DrawDeathEffectComponent.h"

#include "MainScene.h"

namespace {
	struct InfoToShader {
	public:
		XMMATRIX exp_;
		XMMATRIX trans_ortho_;
		float radius_;
		float alpha_;
	};
	struct Vertex {
	public:
		XMFLOAT3 pos_;
		XMFLOAT2 uv_;
	};
}

DrawDeathEffectComponent::DrawDeathEffectComponent(MainScene* scene, GameObjectHandle obj, double max_radius, bool will_kill_object, MatVec::Vector2 offset)
	:MainSceneDrawComponent(scene),
	obj_(obj), max_radius_(max_radius),will_kill_object_(will_kill_object),offset_(offset),time_(0)
{
	if (pipeline_ == nullptr)
	{
		StaticGraphicInit(scene_->mGame);
	}
	NonstaticGraphicInit(scene_->mGame);
}

DrawDeathEffectComponent::~DrawDeathEffectComponent()
{
}

void DrawDeathEffectComponent::Draw()
{
	InfoToShader* map = static_cast<InfoToShader*>(const_buffer_map_);
	MatVec::Vector2 center = obj_->GetPosition() + offset_;
	MatVec::Matrix4x4 exp = MatVec::Expand(max_radius_, max_radius_, 1.0);
	MatVec::Matrix4x4 trans_ortho =
		MatVec::GetOrthoGraphicProjection(600, 900, 0.0, 1.0) *
		MatVec::Translation(MatVec::XY0(center));
	map->exp_ = MatVec::ConvertToXMMATRIX(exp);
	map->trans_ortho_ = MatVec::ConvertToXMMATRIX(trans_ortho);
	map->radius_ = max_radius_ * time_ / 30;
	map->alpha_ = 1.0 - (double)time_ / 30;
	
	Game& game = scene_->mGame;
	game.mdx12.SetGraphicsPipeline(pipeline_);
	game.mdx12.SetRootSignature(root_signature_);
	game.mdx12.SetDescriptorHeap(crv_heap_);
	game.mdx12.SetGraphicsRootDescriptorTable(0, crv_heap_, 0);
	game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLELIST);
	game.mdx12.SetVertexBuffers(vertex_buffer_, 0, sizeof(Vertex) * 4, sizeof(Vertex));
	game.mdx12.SetIndexBuffers(index_buffer_, 6);
	game.mdx12.SetViewports(600, 900, 0, 0, 1.0f, 0.0f);
	game.mdx12.SetScissorrect(0, 900, 0, 600);
	game.mdx12.DrawIndexedInstanced(6, 1, 0, 0, 0);

	//Ž€‚ÊŽžŠÔ
	if (time_ == 29)
	{
		SetDeleteFlag();
		if (will_kill_object_) {
			obj_->SetDeleteFlag();
		}
	}

	time_++;
}

void DrawDeathEffectComponent::StaticGraphicInit(Game& game)
{
	auto vertex_shader = game.mShaderManager.GetDX12ShaderObject(12);
	auto pixel_shader = game.mShaderManager.GetDX12ShaderObject(13);

	vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(Vertex) * 4, L"DrawDeathEffectComponent::vertex_buffer_");
	Vertex vertex_array[4];
	//0 3
	//1 2
	vertex_array[0].pos_ = XMFLOAT3(-1.0f, +1.0f, 0.0f);
	vertex_array[1].pos_ = XMFLOAT3(-1.0f, -1.0f, 0.0f);
	vertex_array[2].pos_ = XMFLOAT3(+1.0f, -1.0f, 0.0f);
	vertex_array[3].pos_ = XMFLOAT3(+1.0f, +1.0f, 0.0f);
	vertex_array[0].uv_ = XMFLOAT2(-1.0f, -1.0f);
	vertex_array[1].uv_ = XMFLOAT2(-1.0f, +1.0f);
	vertex_array[2].uv_ = XMFLOAT2(+1.0f, +1.0f);
	vertex_array[3].uv_ = XMFLOAT2(+1.0f, -1.0f);
	Vertex* vertex_map = static_cast<Vertex*>(game.mdx12.Map(vertex_buffer_));
	std::memcpy(vertex_map, vertex_array, sizeof(vertex_array));
	game.mdx12.Unmap(vertex_buffer_);

	index_buffer_ = game.mdx12.CreateIndexBuffer(6, L"DrawDeathEffectComponent::index_buffer_");
	unsigned int* index_map = static_cast<unsigned int*>(game.mdx12.Map(index_buffer_));
	index_map[0] = 0;
	index_map[1] = 1;
	index_map[2] = 3;
	index_map[3] = 1;
	index_map[4] = 2;
	index_map[5] = 3;
	game.mdx12.Unmap(index_buffer_);

	std::vector<DX12RootParameter> root_params;
	root_params.push_back(DX12RootParameter());
	root_params.back().mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;
	root_params.back().mDescRanges.push_back(DX12DescriptorRange(
		1, DX12Config::DescriptorRangeType::CBV, 0, 0
	));
	root_signature_ = game.mdx12.CreateRootSignature(root_params);

	DX12VertexLayout vertex_layout;
	vertex_layout.push_back(DX12VertexLayoutUnit(
		"POSITION", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
	));
	vertex_layout.push_back(DX12VertexLayoutUnit(
		"TEXCOORD", DX12Config::VertexLayoutFormat::R32G32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));

	pipeline_ = game.mdx12.CreateGraphicsPipeline(
		vertex_shader, pixel_shader, vertex_layout, DX12Config::PrimitiveTopologyType::TRIANGLE, 1, root_signature_, L"DrawDeathEffectComponent::pipeline_"
	);
}

void DrawDeathEffectComponent::NonstaticGraphicInit(Game& game)
{
	const_buffer_ = game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD, sizeof(InfoToShader), L"DrawDeathEffectComponent::const_buffer_");
	const_buffer_map_ = game.mdx12.Map(const_buffer_);

	crv_heap_ = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 1, L"DrawDeathEffectComponent::crv_heap_");
	game.mdx12.CreateConstBufferView(const_buffer_, crv_heap_, 0);
}

boost::shared_ptr<DX12GraphicsPipeline> DrawDeathEffectComponent::pipeline_ = nullptr;
boost::shared_ptr<DX12RootSignature> DrawDeathEffectComponent::root_signature_ = nullptr;
boost::shared_ptr<DX12Resource> DrawDeathEffectComponent::vertex_buffer_ = nullptr;
boost::shared_ptr<DX12Resource> DrawDeathEffectComponent::index_buffer_ = nullptr;
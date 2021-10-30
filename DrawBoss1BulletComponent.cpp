#include "stdafx.h"
#include "DrawBoss1BulletComponent.h"

#include "code/Engine/GameObject.h"
#include "code/Engine/Scene.h"
#include "code/Engine/Game.h"

namespace {
	struct Vertex {
		XMFLOAT3 pos_;
		XMFLOAT2 uv_;
	};
}

DrawBoss1BulletComponent::DrawBoss1BulletComponent(GameObjectHandle obj, boost::shared_ptr<LayerManager> layer_manager)
	:MainSceneDrawComponent(obj,layer_manager,-10.0)
{
	index_ = next_index_.front();
	next_index_.pop();
	matrix_map_ = static_cast<XMMATRIX*>(obj->mScene->mGame.mdx12.Map(const_buffers_[index_]));
	auto deg = mObj->GetRotation();
	exprotmat = MatVec::Expand(20.0, 20.0, 0.0);
	exprotmat = MatVec::Rotate(MatVec::GetQuaternion(MatVec::Vector3(0.0, 0.0, -1.0), deg)) * exprotmat;
}

DrawBoss1BulletComponent::~DrawBoss1BulletComponent()
{
	next_index_.push(index_);
}

void DrawBoss1BulletComponent::StaticGraphicInit(Game& game)
{
	const_buffers_.resize(500);
	desc_heaps_.resize(500);
	for (int n = 0; n < 500; n++)
	{
		const_buffers_[n] = game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD, sizeof(XMMATRIX), L"DrawBoss1BulletComponent::const_buffers_");
		desc_heaps_[n] = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 2, L"DrawBoss1BulletComponent::desc_heaps_");
		game.mTexManager.CreateSRVof(19, desc_heaps_[n], 0);
		game.mdx12.CreateConstBufferView(const_buffers_[n], desc_heaps_[n], 1);
		next_index_.push(n);
	}

	auto vertex_shader = game.mShaderManager.GetDX12ShaderObject(0);
	auto pixel_shader = game.mShaderManager.GetDX12ShaderObject(1);

	DX12VertexLayout vertex_layout;
	vertex_layout.push_back(DX12VertexLayoutUnit(
		"POSITION", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));
	vertex_layout.push_back(DX12VertexLayoutUnit(
		"TEXCOORD", DX12Config::VertexLayoutFormat::R32G32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));

	DX12RootParameter root_param;
	root_param.mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;
	root_param.mDescRanges.push_back(DX12DescriptorRange(
		1, DX12Config::DescriptorRangeType::SRV, 0, 0
	));
	root_param.mDescRanges.push_back(DX12DescriptorRange(
		1, DX12Config::DescriptorRangeType::CBV, 0, 0
	));

	root_signature_ = game.mdx12.CreateRootSignature(root_param);

	graphics_pipeline_ = game.mdx12.CreateGraphicsPipeline(
		vertex_shader, pixel_shader, vertex_layout, DX12Config::PrimitiveTopologyType::TRIANGLE, 1, root_signature_, L"DrawBoss1BulletComponent::graphics_pipeline_"
	);

	index_buffer_ = game.mdx12.CreateIndexBuffer(6, L"DrawBoss1BulletComponent::index_buffer_");
	unsigned int* index_map = static_cast<unsigned int*>(game.mdx12.Map(index_buffer_));
	index_map[0] = 0;
	index_map[1] = 1;
	index_map[2] = 3;
	index_map[3] = 1;
	index_map[4] = 2;
	index_map[5] = 3;
	game.mdx12.Unmap(index_buffer_);

	vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(Vertex) * 4, L"DrawBoss1BulletComponent::vertex_buffer_");
	Vertex* vertex_map = static_cast<Vertex*>(game.mdx12.Map(vertex_buffer_));
	vertex_map[0].uv_ = XMFLOAT2(0.0f, 0.0f);
	vertex_map[1].uv_ = XMFLOAT2(0.0f, 1.0f);
	vertex_map[2].uv_ = XMFLOAT2(1.0f, 1.0f);
	vertex_map[3].uv_ = XMFLOAT2(1.0f, 0.0f);
	vertex_map[0].pos_ = XMFLOAT3(-0.5f, +0.5f, 0.0f);
	vertex_map[1].pos_ = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	vertex_map[2].pos_ = XMFLOAT3(+0.5f, -0.5f, 0.0f);
	vertex_map[3].pos_ = XMFLOAT3(+0.5f, +0.5f, 0.0f);
	game.mdx12.Unmap(vertex_buffer_);
}

void DrawBoss1BulletComponent::Draw()
{
	auto objpos = mObj->GetPosition();
	auto final_mat = MatVec::Translation(MatVec::XY0(objpos)) * exprotmat;
	final_mat = MatVec::GetOrthoGraphicProjection(600.0, 900.0, 0.0, 1.0) * final_mat;
	*matrix_map_ = MatVec::ConvertToXMMATRIX(final_mat);

	auto& game = mObj->mScene->mGame;
	game.mdx12.SetGraphicsPipeline(graphics_pipeline_);
	game.mdx12.SetRootSignature(root_signature_);
	game.mdx12.SetDescriptorHeap(desc_heaps_[index_]);
	game.mdx12.SetGraphicsRootDescriptorTable(0, desc_heaps_[index_], 0);
	game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLELIST);
	game.mdx12.SetVertexBuffers(vertex_buffer_, 0, sizeof(Vertex) * 4, sizeof(Vertex));
	game.mdx12.SetIndexBuffers(index_buffer_, 6);
	game.mdx12.SetViewports(600, 900, 0, 0, 1.0f, 0.0f);
	game.mdx12.SetScissorrect(0, 900, 0, 600);
	game.mdx12.DrawIndexedInstanced(6, 1, 0, 0, 0);
}

std::vector<boost::shared_ptr<DX12Resource>> DrawBoss1BulletComponent::const_buffers_;
std::vector<boost::shared_ptr<DX12DescriptorHeap>> DrawBoss1BulletComponent::desc_heaps_;
boost::shared_ptr<DX12GraphicsPipeline> DrawBoss1BulletComponent::graphics_pipeline_ = nullptr;
boost::shared_ptr<DX12RootSignature> DrawBoss1BulletComponent::root_signature_ = nullptr;
boost::shared_ptr<DX12Resource> DrawBoss1BulletComponent::index_buffer_ = nullptr;
boost::shared_ptr<DX12Resource> DrawBoss1BulletComponent::vertex_buffer_ = nullptr;
std::queue<unsigned int> DrawBoss1BulletComponent::next_index_;
#include "stdafx.h"
#include "DrawHealthBarComponent.h"

#include "GameObject.h"
#include "Scene.h"
#include "EnemyHealthComponent.h"

namespace{
	struct Vertex {
	public:
		XMFLOAT3 position_;
		XMFLOAT2 texcoord_;
	};
	struct InfoToShader {
	public:
		XMMATRIX expand_;
		XMMATRIX translate_;
		XMMATRIX ortho_;
		float r_;
	};
}

DrawHealthBarComponent::DrawHealthBarComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, ComponentHandle<EnemyHealthComponent> health, MatVec::Vector2 offset, double width, double height)
	:MainSceneDrawComponent(object,layer_manager,-7.5),
	center_offset_(offset),width_(width),height_(height),const_buffer_map_(nullptr),frame_(object->mScene->mGame),health_component_(health)
{
	Game& game = mObj->mScene->mGame;
	if (pipeline_ == nullptr)
	{
		StaticGraphicInit(game);
	}
	NonstaticGraphicInit(game);
}

void DrawHealthBarComponent::Draw()
{
	InfoToShader* map = static_cast<InfoToShader*>(const_buffer_map_);
	map->expand_ = MatVec::ConvertToXMMATRIX(MatVec::Expand(width_, height_, 1.0));
	MatVec::Vector2 center = mObj->GetPosition() + center_offset_;
	map->translate_ = MatVec::ConvertToXMMATRIX(MatVec::Translation(center(0), center(1), 0.0));
	map->ortho_ = MatVec::ConvertToXMMATRIX(MatVec::GetOrthoGraphicProjection(600, 900, 0.0, 1.0));
	map->r_ = static_cast<float>(health_component_->GetHealthRate());

	Game& game = mObj->mScene->mGame;
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

	frame_.DrawFrame(game, center(0), center(1), width_, height_, 0.0, 600, 900,MatVec::Vector4(0.0,1.0,0.0,0.5));
}

DrawHealthBarComponent::~DrawHealthBarComponent()
{
}

void DrawHealthBarComponent::StaticGraphicInit(Game& game)
{
	auto vertex_shader = game.mShaderManager.GetDX12ShaderObject(14);
	auto pixel_shader = game.mShaderManager.GetDX12ShaderObject(15);

	DX12VertexLayout vertex_layout;
	vertex_layout.push_back(DX12VertexLayoutUnit(
		"POSITION", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));
	vertex_layout.push_back(DX12VertexLayoutUnit(
		"TEXCOORD", DX12Config::VertexLayoutFormat::R32G32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));

	DX12RootParameter root_param;
	root_param.mDescRanges.push_back(DX12DescriptorRange(
		1, DX12Config::DescriptorRangeType::CBV, 0, 0
	));
	root_param.mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;

	root_signature_ = game.mdx12.CreateRootSignature(root_param, false);

	pipeline_ = game.mdx12.CreateGraphicsPipeline(
		vertex_shader, pixel_shader, vertex_layout,DX12Config::PrimitiveTopologyType::TRIANGLE,1,root_signature_,L"DrawHealthBarComponent::pipeline_"
		);

	vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(Vertex) * 4, L"DrawHealthBarComponent::vertex_buffer_");
	Vertex vertex_array[4];
	//0 3
	//1 2
	vertex_array[0].position_ = XMFLOAT3(-0.5f, +0.5f, 0.0f);
	vertex_array[1].position_ = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	vertex_array[2].position_ = XMFLOAT3(+0.5f, -0.5f, 0.0f);
	vertex_array[3].position_ = XMFLOAT3(+0.5f, +0.5f, 0.0f);
	vertex_array[0].texcoord_ = XMFLOAT2(0.0f, 0.0f);
	vertex_array[1].texcoord_ = XMFLOAT2(0.0f, 1.0f);
	vertex_array[2].texcoord_ = XMFLOAT2(1.0f, 1.0f);
	vertex_array[3].texcoord_ = XMFLOAT2(1.0f, 0.0f);
	Vertex* vertex_map = static_cast<Vertex*>(game.mdx12.Map(vertex_buffer_));
	std::memcpy(vertex_map, vertex_array, sizeof(vertex_array));
	game.mdx12.Unmap(vertex_buffer_);

	index_buffer_ = game.mdx12.CreateIndexBuffer(6, L"DrawHealthBarComponent::index_buffer_");
	unsigned int* index_map = static_cast<unsigned int*>(game.mdx12.Map(index_buffer_));
	index_map[0] = 0;
	index_map[1] = 1;
	index_map[2] = 3;
	index_map[3] = 1;
	index_map[4] = 2;
	index_map[5] = 3;
	game.mdx12.Unmap(index_buffer_);
}

void DrawHealthBarComponent::NonstaticGraphicInit(Game& game)
{
	const_buffer_ = game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD, sizeof(InfoToShader), L"DrawHealthBarComponent::const_buffer_");
	crv_heap_ = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 1, L"DrawHealthBarComponent::crv_heap_");
	game.mdx12.CreateConstBufferView(const_buffer_, crv_heap_, 0);
	const_buffer_map_ = game.mdx12.Map(const_buffer_);
}

boost::shared_ptr<DX12GraphicsPipeline> DrawHealthBarComponent::pipeline_ = nullptr;
boost::shared_ptr<DX12RootSignature> DrawHealthBarComponent::root_signature_ = nullptr;
boost::shared_ptr<DX12Resource> DrawHealthBarComponent::vertex_buffer_ = nullptr;
boost::shared_ptr<DX12Resource> DrawHealthBarComponent::index_buffer_ = nullptr;
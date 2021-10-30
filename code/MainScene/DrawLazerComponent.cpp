#include "DrawLazerComponent.h"

#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"

namespace {
	struct Vertex {
		XMFLOAT3 pos_;
		XMFLOAT2 uv_;
	};
	struct InfoToShader {
		//í∏ì_ç¿ïWÅCUVç¿ïWÇägëÂÇ∑ÇÈçsóÒ
		XMMATRIX expand_matrix_;
		//í∏ì_ç¿ïWÇâÒì]ÅCïΩçsà⁄ìÆÅCê≥ãKâªÇ∑ÇÈçsóÒ
		XMMATRIX pos_matrix_;
		//ê¸ï™ÇÃí∑Ç≥
		float length_;
		//îºâ~ÇÃîºåa
		float r_;
	};
}

DrawLazerComponent::DrawLazerComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, double z)
	:MainSceneDrawComponent(object,layer_manager,z)
{
	Game& game = mObj->mScene->mGame;
	if (graphics_pipeline_ == nullptr)
	{
		StaticGraphicInit(game);
	}
	NonstaticGraphicInit(game);
}

DrawLazerComponent::~DrawLazerComponent()
{
}

void DrawLazerComponent::Draw()
{
	InfoToShader* info_map = static_cast<InfoToShader*>(const_buffer_map_);
	//ägëÂçsóÒ
	double seglength = (a_ - b_).Norm();
	info_map->expand_matrix_ = MatVec::ConvertToXMMATRIX(MatVec::Expand(2 * r_ + seglength, 2 * r_, 1.0));
	//ê¸ï™a_->b_Ç™Ç»Ç∑äpÇãÅÇﬂÇÈ
	auto a_2b_ = b_ - a_;
	double angle = atan2(a_2b_(1), a_2b_(0));
	MatVec::Matrix4x4 pos_matrix = MatVec::Rotate(MatVec::GetQuaternion(MatVec::Vector3(0.0, 0.0, 1.0), angle));
	pos_matrix = MatVec::Translation(MatVec::XY0((a_ + b_) / 2))*pos_matrix;
	pos_matrix = MatVec::GetOrthoGraphicProjection(600.0, 900.0, 0.0, 1.0) * pos_matrix;
	info_map->pos_matrix_ = MatVec::ConvertToXMMATRIX(pos_matrix);
	info_map->length_ = seglength;
	info_map->r_ = r_;

	auto& game = mObj->mScene->mGame;
	game.mdx12.SetGraphicsPipeline(graphics_pipeline_);
	game.mdx12.SetRootSignature(root_signature_);
	game.mdx12.SetDescriptorHeap(desc_heap_);
	game.mdx12.SetGraphicsRootDescriptorTable(0, desc_heap_, 0);
	game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLELIST);
	game.mdx12.SetVertexBuffers(vertex_buffer_, 0, sizeof(Vertex) * 4, sizeof(Vertex));
	game.mdx12.SetIndexBuffers(index_buffer_, 6);
	game.mdx12.SetViewports(600, 900, 0, 0, 0.0f, 1.0f);
	game.mdx12.SetScissorrect(0.0f, 900.0f, 0.0f, 600.0f);
	game.mdx12.DrawIndexedInstanced(6, 1, 0, 0, 0);
}

void DrawLazerComponent::StaticGraphicInit(Game& game)
{
	auto vertex_shader = game.mShaderManager.GetDX12ShaderObject(18);
	auto pixel_shader = game.mShaderManager.GetDX12ShaderObject(19);

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
		1, DX12Config::DescriptorRangeType::CBV, 0, 0
	));
	root_signature_ = game.mdx12.CreateRootSignature(root_param, false);

	graphics_pipeline_ = game.mdx12.CreateGraphicsPipeline(
		vertex_shader, pixel_shader, vertex_layout, DX12Config::PrimitiveTopologyType::TRIANGLE, 1, root_signature_, L"DrawLazerComponent::graphics_pipeline_"
	);

	index_buffer_ = game.mdx12.CreateIndexBuffer(6, L"DrawLazerComponent::index_buffer_");
	unsigned int* index_map = static_cast<unsigned int*>(game.mdx12.Map(index_buffer_));
	index_map[0] = 0;
	index_map[1] = 1;
	index_map[2] = 3;
	index_map[3] = 1;
	index_map[4] = 2;
	index_map[5] = 3;
	game.mdx12.Unmap(index_buffer_);

	vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(Vertex) * 4, L"DrawLazerComponent::vertex_buffer_");
	Vertex* vertex_map = static_cast<Vertex*>(game.mdx12.Map(vertex_buffer_));
	vertex_map[0].pos_ = XMFLOAT3(-0.5f, +0.5f, 0.0f);
	vertex_map[1].pos_ = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	vertex_map[2].pos_ = XMFLOAT3(+0.5f, -0.5f, 0.0f);
	vertex_map[3].pos_ = XMFLOAT3(+0.5f, +0.5f, 0.0f);
	vertex_map[0].uv_ = XMFLOAT2(-0.5f, -0.5f);
	vertex_map[1].uv_ = XMFLOAT2(-0.5f, +0.5f);
	vertex_map[2].uv_ = XMFLOAT2(+0.5f, +0.5f);
	vertex_map[3].uv_ = XMFLOAT2(+0.5f, -0.5f);
	game.mdx12.Unmap(vertex_buffer_);
}

void DrawLazerComponent::NonstaticGraphicInit(Game& game)
{
	const_buffer_ = game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD, sizeof(InfoToShader), L"DrawLazerComponent::const_buffer_");
	const_buffer_map_ = game.mdx12.Map(const_buffer_);

	desc_heap_ = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 1, L"DrawLazerComponent::desc_heap_");
	game.mdx12.CreateConstBufferView(const_buffer_, desc_heap_, 0);
}

boost::shared_ptr<DX12GraphicsPipeline> DrawLazerComponent::graphics_pipeline_ = nullptr;
boost::shared_ptr<DX12RootSignature> DrawLazerComponent::root_signature_ = nullptr;
boost::shared_ptr<DX12Resource> DrawLazerComponent::index_buffer_ = nullptr;
boost::shared_ptr<DX12Resource> DrawLazerComponent::vertex_buffer_ = nullptr;

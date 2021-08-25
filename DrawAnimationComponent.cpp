#include "stdafx.h"
#include "DrawAnimationComponent.h"

#include "GameObject.h"
#include "Scene.h"

namespace {
	struct Vertex {
		XMFLOAT3 pos_;
		XMFLOAT2 uv_;
	};
	struct InfoToShader {
		XMMATRIX pos_matrix_;
		XMMATRIX uv_matrix_;
	};
}

DrawAnimationComponent::DrawAnimationComponent(GameObjectHandle obj, boost::shared_ptr<LayerManager> layer_manager, unsigned int texture_id, double flame_width, double flame_height, unsigned int column, unsigned int row, double z, MatVec::Vector2 offset, unsigned int flame_num, bool loop, std::function<void(GameObjectHandle)> terminal)
	:MainSceneDrawComponent(obj, layer_manager, z),
	center_offset_(offset),flame_width_(flame_width),flame_height_(flame_height),
	column_(column),row_(row),flame_num_(flame_num),loop_(loop),terminal_(terminal),counter_(0)
{
	if (graphics_pipeline_ == nullptr)
	{
		StaticGraphicInit(mObj->mScene->mGame);
	}
	NonstaticGraphicInit(mObj->mScene->mGame,texture_id);
}

DrawAnimationComponent::~DrawAnimationComponent()
{
}

void DrawAnimationComponent::Draw()
{
	//�`��ʒu�����߂�s��
	MatVec::Matrix4x4 pos_matrix = MatVec::Expand(flame_width_, flame_height_, 1.0);
	pos_matrix = MatVec::Rotate(MatVec::GetQuaternion(MatVec::Vector3(0, 0, 1), mObj->GetRotation())) * pos_matrix;
	pos_matrix = MatVec::Translation(MatVec::XY0(mObj->GetPosition() + center_offset_))*pos_matrix;
	pos_matrix = MatVec::GetOrthoGraphicProjection(600, 900, 0.0, 1.0)*pos_matrix;

	//�`�悷��摜�̈ʒu�����߂�s��
	MatVec::Matrix4x4 uv_matrix = MatVec::Expand(1.0 / column_, 1.0 / row_, 1.0);
	//�\������摜�͍�����counter_%column_�C�ォ��counter_/column_�Ԗ�(0-index)
	//UV���W�͂��Ƃ��ƍ����(0,0)�Ƃ��Ă���
	uv_matrix = MatVec::Translation(
		static_cast<double>(counter_ % column_) / column_,
		static_cast<double>(counter_ / column_) / row_,
		0.0
	)*uv_matrix;

	InfoToShader* info_map = static_cast<InfoToShader*>(const_buffer_map_);
	info_map->pos_matrix_ = MatVec::ConvertToXMMATRIX(pos_matrix);
	info_map->uv_matrix_ = MatVec::ConvertToXMMATRIX(uv_matrix);

	Game& game = mObj->mScene->mGame;
	game.mdx12.SetGraphicsPipeline(graphics_pipeline_);
	game.mdx12.SetRootSignature(root_signature_);
	game.mdx12.SetDescriptorHeap(desc_heap_);
	game.mdx12.SetGraphicsRootDescriptorTable(0, desc_heap_, 0);
	game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLELIST);
	game.mdx12.SetVertexBuffers(vertex_buffer_,0,sizeof(Vertex)*4,sizeof(Vertex));
	game.mdx12.SetIndexBuffers(index_buffer_,6);
	game.mdx12.SetViewports(600, 900, 0, 0, 0.0, 1.0);
	game.mdx12.SetScissorrect(0.0f,900.0f,0.0f,600.0f);
	game.mdx12.DrawIndexedInstanced(6, 1, 0, 0, 0);

	counter_++;
	if (counter_ == flame_num_)
	{
		if (!loop_) {
			terminal_(mObj);
			SetDeleteFlag();
		}
		else {
			counter_ -= flame_num_;
		}
	}
}

void DrawAnimationComponent::StaticGraphicInit(Game& game)
{
	auto vertex_shader = game.mShaderManager.GetDX12ShaderObject(16);
	auto pixel_shader = game.mShaderManager.GetDX12ShaderObject(17);

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
		vertex_shader, pixel_shader, vertex_layout, DX12Config::PrimitiveTopologyType::TRIANGLE, 1,
		root_signature_, L"DrawAnimationComponent::graphics_pipeline_"
	);

	index_buffer_ = game.mdx12.CreateIndexBuffer(6, L"DrawAnimationComponent::index_buffer_");
	unsigned int* index_map = static_cast<unsigned int*>(game.mdx12.Map(index_buffer_));
	index_map[0] = 0;
	index_map[1] = 1;
	index_map[2] = 3;
	index_map[3] = 1;
	index_map[4] = 2;
	index_map[5] = 3;
	game.mdx12.Unmap(index_buffer_);

	vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(Vertex) * 4, L"DrawAnimationComponent::vertex_buffer_");
	void* vertex_map = game.mdx12.Map(vertex_buffer_);
	Vertex vertexs_[4];
	vertexs_[0].uv_ = XMFLOAT2(0.0f, 0.0f);
	vertexs_[1].uv_ = XMFLOAT2(0.0f, 1.0f);
	vertexs_[2].uv_ = XMFLOAT2(1.0f, 1.0f);
	vertexs_[3].uv_ = XMFLOAT2(1.0f, 0.0f);
	vertexs_[0].pos_ = XMFLOAT3(-0.5f, +0.5f, 0.0f);
	vertexs_[1].pos_ = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	vertexs_[2].pos_ = XMFLOAT3(+0.5f, -0.5f, 0.0f);
	vertexs_[3].pos_ = XMFLOAT3(+0.5f, +0.5f, 0.0f);
	std::memcpy(vertex_map, vertexs_, sizeof(vertexs_));
	game.mdx12.Unmap(vertex_buffer_);
}

void DrawAnimationComponent::NonstaticGraphicInit(Game& game, unsigned int texture_id)
{
	const_buffer_ = game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD, sizeof(InfoToShader), L"DrawAnimationComponent::const_buffer_");
	desc_heap_ = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 2, L"DrawAnimationComponent::desc_heap_");
	game.mTexManager.CreateSRVof(texture_id, desc_heap_, 0);
	game.mdx12.CreateConstBufferView(const_buffer_, desc_heap_, 1);
	const_buffer_map_ = game.mdx12.Map(const_buffer_);
}

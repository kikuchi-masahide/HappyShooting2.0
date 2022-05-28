#include "MainSceneEndingLayer.h"

#include "../Engine/Scene.h"

namespace {
	struct InfoToShader {
	public:
	};
	struct Vertex {
	public:
		XMFLOAT3 pos_;
		XMFLOAT2 uv_;
	};
}

MainSceneEndingLayer::MainSceneEndingLayer(Scene* scene, DrawComponentsMultiset* draw_components)
	:MainSceneBaseLayer(scene,draw_components),
	frame_(scene->mGame)
{
	GraphicInit(scene->mGame);
}

MainSceneEndingLayer::~MainSceneEndingLayer()
{
}

void MainSceneEndingLayer::UniqueDraw()
{
	auto& game = scene_->mGame;
	game.mdx12.OpenRenderTarget(pera_rtv_, 0);
	frame_.DrawFrame(game, 0.0, 0.0, 600.0, 900.0, 0.0, 600.0, 900.0);
	game.OpenSwapChain(0);
	game.mdx12.SetGraphicsPipeline(pipeline_);
	game.mdx12.SetRootSignature(rootsignature_);
	game.mdx12.SetDescriptorHeap(heap_);
	game.mdx12.SetGraphicsRootDescriptorTable(0, heap_, 0);
	//HACK:�����GraphicsPipeline�̐ݒ�i�K�łقڌ��܂��Ă��邽�߁A���̊֐��Ăяo���͏ȗ��ł���̂ł�
	game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLELIST);
	//HACK:����sizeof(Vertex)*4,sizeof(Vertex),6�̍��̏��𒸓_�o�b�t�@�E�C���f�b�N�X�o�b�t�@�Ɋ܂܂���
	game.mdx12.SetVertexBuffers(vertex_,0,sizeof(Vertex)*4,sizeof(Vertex));
	game.mdx12.SetIndexBuffers(index_,6);
	game.mdx12.SetViewports(600.0, 900.0, 0, 0,1.0f,0.0f);
	game.mdx12.SetScissorrect(0, 900, 0, 600);
	game.mdx12.DrawIndexedInstanced(6, 1, 0, 0, 0);
	game.CloseSwapChain();
}

void MainSceneEndingLayer::GraphicInit(Game& game)
{
	DX12VertexLayout vertex_layout;
	//HACK:���3���I�v�V�����ɂ����I�t���悳����
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
	rootsignature_ = game.mdx12.CreateRootSignature(root_param);
	auto vertex_shader = game.mShaderManager.GetDX12ShaderObject(32);
	auto pixel_shader = game.mShaderManager.GetDX12ShaderObject(33);
	pipeline_ = game.mdx12.CreateGraphicsPipeline(
		vertex_shader,pixel_shader,vertex_layout,DX12Config::PrimitiveTopologyType::TRIANGLE,1,rootsignature_,L"MainSceneEndingLayer::pipeline_"
	);
	vertex_ = game.mdx12.CreateVertexBuffer(sizeof(Vertex), L"MainSceneEndingLayer::vertex_");
	//HACK:�܂��ł�����ӂ̗��ꖳ���񏑂��Ă�̂ŁA���͂�����ւ���g���܂킹��悤�l����
	auto vertex_map = static_cast<Vertex*>(game.mdx12.Map(vertex_));
	vertex_map[0].pos_ = MatVec::ConvertToXMFLOAT3(MatVec::Vector3(-1.0, 1.0, 0.0));
	vertex_map[1].pos_ = MatVec::ConvertToXMFLOAT3(MatVec::Vector3(-1.0, -1.0, 0.0));
	vertex_map[2].pos_ = MatVec::ConvertToXMFLOAT3(MatVec::Vector3(1.0 / 3, -1.0, 0.0));
	vertex_map[3].pos_ = MatVec::ConvertToXMFLOAT3(MatVec::Vector3(1.0 / 3, 1.0, 0.0));
	game.mdx12.Unmap(vertex_);
	index_ = game.mdx12.CreateIndexBuffer(6, L"MainSceneEndingLayer::index_buffer_");
	unsigned int* index_map = static_cast<unsigned int*>(game.mdx12.Map(index_));
	index_map[0] = 0;
	index_map[1] = 1;
	index_map[2] = 3;
	index_map[3] = 1;
	index_map[4] = 3;
	index_map[5] = 2;
	game.mdx12.Unmap(index_);
	const_ = game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD, sizeof(InfoToShader), L"MainSceneEndingLayer::const_");
	heap_ = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 2, L"MainSceneEndingLayer::heap_");
	game.mdx12.CreateConstBufferView(const_, heap_, 0);
	game.mdx12.CreateShaderResourceView(pera_texture_, heap_, 1, 28);
}

#include "MainSceneClippingLayer.h"

#include "../Engine/Scene.h"

namespace {
	struct Vertex{
	public:
		XMFLOAT3 pos_;
		XMFLOAT2 uv_;
	};
	struct InfoToShader {
	public:
		XMMATRIX mat_;
		//[0.0,1.0]x[0.0,1.0]であるuv座標を[-300,+300]x[-450,+450]に直し，自機との距離計算をする
		XMMATRIX uv_exp_;
		//自機中心座標([-300,+300]x[-450,+450]座標)
		XMFLOAT2 myself_;
		//自機との距離がこれ以下であるピクセルは出力する
		float r_;
	};
}

MainSceneClippingLayer::MainSceneClippingLayer(Scene* scene, DrawComponentsMultiset* draw_components, GameObjectHandle myself)
	:MainSceneBaseLayer(scene,draw_components),
	myself_(myself),frame_(scene->mGame)
{
	GraphicInit();
}

MainSceneClippingLayer::~MainSceneClippingLayer()
{
}

void MainSceneClippingLayer::UniqueDraw()
{
	auto& game = scene_->mGame;
	InfoToShader* const_map = static_cast<InfoToShader*>(game.mdx12.Map(const_buffer_));
	unsigned int t = GetLayert();
	if (t < shrinking_period_)
	{
		const_map->r_ = (min_r_ - 900.0) * t / (shrinking_period_ - 1) + 900.0;
	}
	else if (t < shrinking_period_ + maintain_period_)
	{
		const_map->r_ = min_r_;
	}
	else
	{
		const_map->r_ = (900.0 - min_r_) * (t - shrinking_period_ - maintain_period_) / (clearing_period_ - 1) + min_r_;
		const_map->r_ = min(900.0, const_map->r_);
	}
	const_map->myself_ = MatVec::ConvertToXMFLOAT2(myself_->GetPosition());
	game.mdx12.Unmap(const_buffer_);

	game.OpenSwapChain(0);
	game.mdx12.SetGraphicsPipeline(graphics_pipeline_);
	game.mdx12.SetDescriptorHeap(desc_heap_);
	game.mdx12.SetRootSignature(root_signature_);
	game.mdx12.SetGraphicsRootDescriptorTable(0, desc_heap_, 0);
	game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLELIST);
	game.mdx12.SetVertexBuffers(vertex_buffer_,0,sizeof(Vertex)*4,sizeof(Vertex));
	game.mdx12.SetIndexBuffers(index_buffer_,6);
	game.mdx12.SetViewports(900, 900, 0, 0, 1.0f, 0.0f);
	game.mdx12.SetScissorrect(0.0f, 900.0f, 0.0f, 600.0f);
	game.mdx12.DrawIndexedInstanced(6, 1, 0, 0, 0);

	frame_.DrawFrame(scene_->mGame, -150.0, 0.0, 600.0, 900.0, 0.0, 900.0, 900.0);

	game.CloseSwapChain();
}

MatVec::Matrix4x4 MainSceneClippingLayer::GetLayerTransform()
{
	return MatVec::Identity4x4();
}

void MainSceneClippingLayer::GraphicInit()
{
	auto& game = scene_->mGame;

	DX12RootParameter root_param;
	root_param.mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;
	root_param.mDescRanges.push_back(DX12DescriptorRange(1, DX12Config::DescriptorRangeType::CBV, 0, 0));
	root_param.mDescRanges.push_back(DX12DescriptorRange(1, DX12Config::DescriptorRangeType::SRV, 0, 0));

	root_signature_ = game.mdx12.CreateRootSignature(root_param, true);

	auto vertex = game.mShaderManager.GetDX12ShaderObject(24);
	auto pixel = game.mShaderManager.GetDX12ShaderObject(25);

	DX12VertexLayout vertex_layout;
	vertex_layout.push_back(DX12VertexLayoutUnit("POSITION", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0));
	vertex_layout.push_back(DX12VertexLayoutUnit("TEXCOORD", DX12Config::VertexLayoutFormat::R32G32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0));

	graphics_pipeline_ = game.mdx12.CreateGraphicsPipeline(
		vertex, pixel, vertex_layout, DX12Config::PrimitiveTopologyType::TRIANGLE, 1, root_signature_, L"MainSceneClippingLayer::graphics_pipeline_"
	);

	vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(Vertex) * 4, L"MainSceneClippingLayer::vertex_buffer_");
	auto vertex_map = static_cast<Vertex*>(game.mdx12.Map(vertex_buffer_));
	vertex_map[0].pos_ = XMFLOAT3(-450.0f, +450.0f, 0.0f);
	vertex_map[1].pos_ = XMFLOAT3(-450.0f, -450.0f, 0.0f);
	vertex_map[2].pos_ = XMFLOAT3(+150.0f, -450.0f, 0.0f);
	vertex_map[3].pos_ = XMFLOAT3(+150.0f, +450.0f, 0.0f);
	vertex_map[0].uv_ = XMFLOAT2(0.0f, 0.0f);
	vertex_map[1].uv_ = XMFLOAT2(0.0f, 1.0f);
	vertex_map[2].uv_ = XMFLOAT2(1.0f, 1.0f);
	vertex_map[3].uv_ = XMFLOAT2(1.0f, 0.0f);
	game.mdx12.Unmap(vertex_buffer_);
	index_buffer_ = game.mdx12.CreateIndexBuffer(6, L"MainSceneClippingLayer::index_buffer_");
	auto index_map = static_cast<unsigned int*>(game.mdx12.Map(index_buffer_));
	index_map[0] = 0;
	index_map[1] = 1;
	index_map[2] = 3;
	index_map[3] = 1;
	index_map[4] = 2;
	index_map[5] = 3;
	game.mdx12.Unmap(index_buffer_);

	desc_heap_ = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 2, L"MainSceneClippingLayer::desc_heap_");
	//0:CBV,1:SRV
	const_buffer_ = game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD, sizeof(InfoToShader), L"MainSceneClippingLayer::const_buffer_");
	game.mdx12.CreateConstBufferView(const_buffer_, desc_heap_, 0);
	game.mdx12.CreateShaderResourceView(pera_texture_, desc_heap_, 1, 28);
	//行列値は不変なので
	InfoToShader* const_map = static_cast<InfoToShader*>(game.mdx12.Map(const_buffer_));
	MatVec::Matrix4x4 mat = MatVec::GetOrthoGraphicProjection(900.0, 900.0, 0.0, 1.0);
	const_map->mat_ = MatVec::ConvertToXMMATRIX(mat);
	MatVec::Matrix4x4 uv_exp = MatVec::Translation(-300.0, +450.0, 0.0) * MatVec::Expand(600.0, -900.0, 1.0);
	const_map->uv_exp_ = MatVec::ConvertToXMMATRIX(uv_exp);
	game.mdx12.Unmap(const_buffer_);
}

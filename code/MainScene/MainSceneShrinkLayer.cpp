#include "MainSceneShrinkLayer.h"

#include "../Engine/Scene.h"

namespace {
	struct Vertex {
	public:
		XMFLOAT3 pos_;
		XMFLOAT2 uv_;
	};
	struct InfoToShader {
	public:
		//[-300,300]x[-450,450]ç¿ïWÇ[-1,1]x[-1,1]Ç…ïœä∑Ç∑ÇÈçsóÒ
		XMMATRIX mat_;
		//ï`âÊÇ∑ÇÈóÃàÊÇÃ4ì_
		//4Ç¬ÇÃê¸ï™ÇÃâEë§Ç»ÇÁï`âÊ
		XMFLOAT2 anchor_0_;
		XMFLOAT2 anchor_1_;
		XMFLOAT2 anchor_2_;
		XMFLOAT2 anchor_3_;
	};
}

MainSceneShrinkLayer::MainSceneShrinkLayer(Scene* scene, DrawComponentsMultiset* draw_components)
	:MainSceneBaseLayer(scene,draw_components),
	frame_(scene->mGame)
{
	GraphicsInit(scene->mGame);
}

MainSceneShrinkLayer::~MainSceneShrinkLayer()
{
}

void MainSceneShrinkLayer::UniqueDraw()
{
	//é©ã@à⁄ìÆêßå¿
	double rotate;
	double expand;
	int t = GetLayert();
	if (t < shrink_period_)
	{
		rotate = max_rotate_angle_ * t / shrink_period_;
		expand = (1.0 * (shrink_period_ - t) + max_expand_ratio_ * t) / shrink_period_;
	}
	else if (t < whole_period_ + 1 - shrink_period_)
	{
		rotate = max_rotate_angle_;
		expand = max_expand_ratio_;
	}
	else {
		int c = whole_period_ + 1 - t;
		rotate = max_rotate_angle_ * c / shrink_period_;
		expand = (1.0 * (shrink_period_ - c) + max_expand_ratio_ * c) / shrink_period_;
	}
	//pos_adjust_[n]ÇÕanchor[n]Ça_ÅCanchor[n+1]Çb_Ç∆Ç∑ÇÈ
	MatVec::Vector2 anchor[5];
	anchor[0] = MatVec::Vector2(-300.0, -450.0);
	anchor[1] = MatVec::Vector2(-300.0, +450.0);
	anchor[2] = MatVec::Vector2(+300.0, +450.0);
	anchor[3] = MatVec::Vector2(+300.0, -450.0);
	anchor[4] = MatVec::Vector2(-300.0, -450.0);
	InfoToShader* info_map = static_cast<InfoToShader*>(const_buffer_map_);
	//anchorÇâÒì]ÅCägëÂèkè¨Ç≥ÇπÇÈ
	for (int n = 0; n < 5; n++)
	{
		anchor[n] *= expand;
		double x = anchor[n](0);
		double y = anchor[n](1);
		anchor[n] = MatVec::Vector2(x * cos(rotate) - y * sin(rotate), x * sin(rotate) + y * cos(rotate));
	}
	info_map->anchor_0_ = MatVec::ConvertToXMFLOAT2(anchor[0]);
	info_map->anchor_1_ = MatVec::ConvertToXMFLOAT2(anchor[1]);
	info_map->anchor_2_ = MatVec::ConvertToXMFLOAT2(anchor[2]);
	info_map->anchor_3_ = MatVec::ConvertToXMFLOAT2(anchor[3]);

	auto& game = scene_->mGame;
	game.OpenSwapChain(0);
	game.mdx12.SetGraphicsPipeline(graphics_pipeline_);
	game.mdx12.SetRootSignature(root_signature_);
	game.mdx12.SetDescriptorHeap(desc_heap_);
	game.mdx12.SetGraphicsRootDescriptorTable(0, desc_heap_, 0);
	game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLELIST);
	game.mdx12.SetVertexBuffers(vertex_buffer_,0,sizeof(Vertex)*4,sizeof(Vertex));
	game.mdx12.SetIndexBuffers(index_buffer_,6);
	game.mdx12.SetViewports(900, 900, 0, 0, 1.0f, 0.0f);
	game.mdx12.SetScissorrect(0.0f, 900.0f, 0.0f, 600.0f);
	game.mdx12.DrawIndexedInstanced(6, 1, 0, 0, 0);
	frame_.DrawFrame(game, -150.0, 0.0, 600.0 * expand, 900.0 * expand, rotate, 900.0, 900.0);

	game.CloseSwapChain();
}

MatVec::Matrix4x4 MainSceneShrinkLayer::GetLayerTransform()
{
	return MatVec::Identity4x4();
}

void MainSceneShrinkLayer::GraphicsInit(Game& game)
{
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

	auto vertex = game.mShaderManager.GetDX12ShaderObject(26);
	auto pixel = game.mShaderManager.GetDX12ShaderObject(27);

	graphics_pipeline_ = game.mdx12.CreateGraphicsPipeline(
		vertex, pixel, vertex_layout, DX12Config::PrimitiveTopologyType::TRIANGLE, 1, root_signature_,
		L"MainSceneShrinkLayer::graphics_pipeline_"
	);

	vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(Vertex) * 4, L"MainSceneShrinkLayer::vertex_buffer_");
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
	index_buffer_ = game.mdx12.CreateIndexBuffer(6, L"MainSceneShrinkLayer::index_buffer_");
	auto index_map = static_cast<unsigned int*>(game.mdx12.Map(index_buffer_));
	index_map[0] = 0;
	index_map[1] = 1;
	index_map[2] = 3;
	index_map[3] = 1;
	index_map[4] = 2;
	index_map[5] = 3;
	game.mdx12.Unmap(index_buffer_);

	const_buffer_ = game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD, sizeof(InfoToShader), L"MainSceneShrinkLayer::const_buffer_");
	const_buffer_map_ = game.mdx12.Map(const_buffer_);
	MatVec::Matrix4x4 mat = MatVec::GetOrthoGraphicProjection(900.0, 900.0, 0.0, 1.0);
	static_cast<InfoToShader*>(const_buffer_map_)->mat_ = MatVec::ConvertToXMMATRIX(mat);

	desc_heap_ = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 2, L"MainSceneShrinkLayer::desc_heap_");
	game.mdx12.CreateShaderResourceView(pera_texture_, desc_heap_, 0, 28);
	game.mdx12.CreateConstBufferView(const_buffer_, desc_heap_, 1);
}

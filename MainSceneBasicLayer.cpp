#include "stdafx.h"
#include "MainSceneBasicLayer.h"
#include "MainScene.h"

MainSceneBasicLayer::MainSceneBasicLayer(MainScene* scene, ComponentHandle<MyselfPosAndAngleComponent> myself_pos_component)
	:MainSceneBaseLayer(scene,myself_pos_component),line_frame(scene->mGame)
{
	GraphicsInit();
}

MainSceneBasicLayer::~MainSceneBasicLayer()
{
}

void MainSceneBasicLayer::UniqueDraw()
{
	Game& game = GetGame();
	game.OpenSwapChain(0);
	
	game.mdx12.SetGraphicsPipeline(graphics_pipeline_);
	game.mdx12.SetRootSignature(rootsignature_);
	game.mdx12.SetDescriptorHeap(pera_srv_);
	game.mdx12.SetGraphicsRootDescriptorTable(0, pera_srv_,0);
	game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLELIST);
	game.mdx12.SetVertexBuffers(vertex_buffer_, 0, sizeof(Vertex) * 4, sizeof(Vertex));
	game.mdx12.SetIndexBuffers(index_buffer_, 6);
	game.mdx12.SetViewports(900, 900, 0, 0, 1.0f, 0.0f);
	game.mdx12.SetScissorrect(0, 900, 0, 600);

	game.mdx12.DrawIndexedInstanced(6, 1, 0, 0, 0);

	//枠線を描く
	line_frame.DrawFrame(GetGame(),-150, 0, 600, 900, 0, 900, 900);

	game.CloseSwapChain();
}

void MainSceneBasicLayer::GraphicsInit()
{
	Game& game = GetGame();

	auto vertex_shader = game.mShaderManager.GetDX12ShaderObject(2);
	auto pixel_shader = game.mShaderManager.GetDX12ShaderObject(3);

	//頂点レイアウトは，
	//クライアント-1~1座標，uv
	DX12VertexLayout vertex_layout;
	vertex_layout.push_back(DX12VertexLayoutUnit(
		"POSITION", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));
	vertex_layout.push_back(DX12VertexLayoutUnit(
		"TEXCOORD", DX12Config::VertexLayoutFormat::R32G32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));

	//ルートパラメータはペラポリゴンのみ
	DX12RootParameter root_parameter;
	root_parameter.mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;
	root_parameter.mDescRanges.push_back(DX12DescriptorRange(
		1, DX12Config::DescriptorRangeType::SRV, 0, 0
	));
	rootsignature_ = game.mdx12.CreateRootSignature(root_parameter);

	graphics_pipeline_ = game.mdx12.CreateGraphicsPipeline(vertex_shader, pixel_shader,
		vertex_layout, DX12Config::PrimitiveTopologyType::TRIANGLE, 1, rootsignature_,
		L"MainSceneBasicLayer::graphics_pipeline_");

	vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(Vertex) * 4, L"MainSceneBasicLayer VertexBuffer");
	Vertex* vertex_map = static_cast<Vertex*>(game.mdx12.Map(vertex_buffer_));
	//0 3
	//1 2
	vertex_map[0] = Vertex(
		-1.0f, 1.0f, 0.0f,
		0.0f, 0.0f
	);
	vertex_map[1] = Vertex(
		-1.0f, -1.0f, 0.0f,
		0.0f, 1.0f
	);
	vertex_map[2] = Vertex(
		1.0f / 3, -1.0f, 0.0f,
		1.0f, 1.0f
	);
	vertex_map[3] = Vertex(
		1.0f / 3, 1.0f, 0.0f,
		1.0f, 0.0f
	);
	game.mdx12.Unmap(vertex_buffer_);

	index_buffer_ = game.mdx12.CreateIndexBuffer(6, L"MainSceneBasicLayer IndexBuffer");
	unsigned int* index_map = static_cast<unsigned int*>(game.mdx12.Map(index_buffer_));
	index_map[0] = 0;
	index_map[1] = 1;
	index_map[2] = 3;
	index_map[3] = 1;
	index_map[4] = 3;
	index_map[5] = 2;
	game.mdx12.Unmap(index_buffer_);
}

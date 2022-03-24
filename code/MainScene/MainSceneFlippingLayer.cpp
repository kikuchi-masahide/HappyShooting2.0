#include "MainSceneFlippingLayer.h"

#include "../Engine/Scene.h"

namespace {
	struct Vertex {
		XMFLOAT3 pos_;
		XMFLOAT2 uv_;
	};
}

MainSceneFlippingLayer::MainSceneFlippingLayer(Scene* scene, DrawComponentsMultiset* draw_components)
	:MainSceneBaseLayer(scene,draw_components)
{
	GraphicsInit(scene_->mGame);
}

MainSceneFlippingLayer::~MainSceneFlippingLayer()
{
}

void MainSceneFlippingLayer::UniqueDraw()
{
	//板の回転角度(0 <= theta < 2PI)
	double theta = GetRotation();
	((Vertex*)vertex_map_)[0].pos_ = MatVec::ConvertToXMFLOAT3(MatVec::Vector3((-1.0 - 2.0 * cos(theta)) / 3, (+5.0 - sin(theta)) / 5, 0.0));
	((Vertex*)vertex_map_)[1].pos_ = MatVec::ConvertToXMFLOAT3(MatVec::Vector3((-1.0 - 2.0 * cos(theta)) / 3, (-5.0 - sin(theta)) / 5, 0.0));
	((Vertex*)vertex_map_)[2].pos_ = MatVec::ConvertToXMFLOAT3(MatVec::Vector3((-1.0 + 2.0 * cos(theta)) / 3, (-5.0 + sin(theta)) / 5, 0.0));
	((Vertex*)vertex_map_)[3].pos_ = MatVec::ConvertToXMFLOAT3(MatVec::Vector3((-1.0 + 2.0 * cos(theta)) / 3, (+5.0 + sin(theta)) / 5, 0.0));
	auto& game = GetGame();
	//表側を表示
	if (theta < PI / 2 || theta > PI * 3 / 2)
	{
		game.mdx12.SetGraphicsPipeline(pipeline_front_);
		game.mdx12.SetRootSignature(root_signature_front_);
	}
	//裏側を表示
	else {
		game.mdx12.SetGraphicsPipeline(pipeline_back_);
		game.mdx12.SetRootSignature(root_signature_back_);
	}
	game.OpenSwapChain(0);
	game.mdx12.SetDescriptorHeap(pera_srv_);
	game.mdx12.SetGraphicsRootDescriptorTable(0, pera_srv_, 0);
	game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLELIST);
	game.mdx12.SetVertexBuffers(vertex_buffer_, 0, sizeof(Vertex) * 4, sizeof(Vertex));
	game.mdx12.SetIndexBuffers(index_buffer_, 6);
	game.mdx12.SetViewports(900, 900, 0, 0, 1.0f, 0.0f);
	game.mdx12.SetScissorrect(0.0f, 900.0f, 0.0f, 600.0f);
	game.mdx12.DrawIndexedInstanced(6, 1, 0, 0, 0);

	//枠線
	game.mdx12.SetGraphicsPipeline(pipeline_frame_);
	game.mdx12.SetRootSignature(root_signature_frame_);
	game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::LINESTRIP);
	game.mdx12.SetVertexBuffers(vertex_buffer_, 0, sizeof(Vertex) * 5, sizeof(Vertex));
	game.mdx12.SetViewports(900, 900, 0, 0, 1.0f, 0.0f);
	game.mdx12.SetScissorrect(0.0f, 900.0f, 0.0f, 600.0f);
	game.mdx12.DrawInstanced(4, 1, 0, 0);
	game.CloseSwapChain();
}

MatVec::Matrix4x4 MainSceneFlippingLayer::GetLayerTransform()
{
	//点(x,y)は(xcosθ,y+0.3xsinθ)に移動する
	double theta = GetRotation();
	MatVec::Matrix4x4 ret = MatVec::Identity4x4();
	ret(0, 0) = cos(theta);
	ret(1, 0) = 0.3 * sin(theta);
	return ret;
}

void MainSceneFlippingLayer::GraphicsInit(Game& game)
{
	//表側の初期化
	//シェーダはBasicLayerを流用
	auto vertex = game.mShaderManager.GetDX12ShaderObject(2);
	auto pixel = game.mShaderManager.GetDX12ShaderObject(3);
	DX12VertexLayout layout;
	layout.push_back(DX12VertexLayoutUnit(
		"POSITION", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));
	layout.push_back(DX12VertexLayoutUnit(
		"TEXCOORD", DX12Config::VertexLayoutFormat::R32G32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));
	//使うのはSRVのみ
	DX12RootParameter rootparam;
	rootparam.mDescRanges.push_back(DX12DescriptorRange(
		1, DX12Config::DescriptorRangeType::SRV, 0, 0
	));
	rootparam.mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;
	root_signature_front_ = game.mdx12.CreateRootSignature(rootparam);
	pipeline_front_ = game.mdx12.CreateGraphicsPipeline(
		vertex, pixel, layout, DX12Config::PrimitiveTopologyType::TRIANGLE, 1, root_signature_front_, L"MainSceneFlippingLayer::pipeline_front_"
	);

	//裏側の初期化
	vertex = game.mShaderManager.GetDX12ShaderObject(28);
	pixel = game.mShaderManager.GetDX12ShaderObject(29);
	root_signature_back_ = game.mdx12.CreateRootSignature(rootparam);
	pipeline_back_ = game.mdx12.CreateGraphicsPipeline(
		vertex, pixel, layout, DX12Config::PrimitiveTopologyType::TRIANGLE, 1, root_signature_back_, L"MainSceneFlippingLayer::pipeline_back_"
	);

	//フレーム用
	vertex = game.mShaderManager.GetDX12ShaderObject(30);
	pixel = game.mShaderManager.GetDX12ShaderObject(31);
	DX12RootParameter rootparam_frame;
	rootparam_frame.mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;
	root_signature_frame_ = game.mdx12.CreateRootSignature(rootparam_frame, false);
	pipeline_frame_ = game.mdx12.CreateGraphicsPipeline(
		vertex, pixel, layout, DX12Config::PrimitiveTopologyType::LINE, 1, root_signature_frame_, L"MainSceneFlippingLayer::pipeline_frame_"
	);

	vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(Vertex) * 5, L"MainSceneFlippingLayer::vertex_buffer_");
	vertex_map_ = game.mdx12.Map(vertex_buffer_);
	((Vertex*)vertex_map_)[0].uv_ = MatVec::ConvertToXMFLOAT2(MatVec::Vector2(0.0f, 0.0f));
	((Vertex*)vertex_map_)[1].uv_ = MatVec::ConvertToXMFLOAT2(MatVec::Vector2(0.0f, 1.0f));
	((Vertex*)vertex_map_)[2].uv_ = MatVec::ConvertToXMFLOAT2(MatVec::Vector2(1.0f, 1.0f));
	((Vertex*)vertex_map_)[3].uv_ = MatVec::ConvertToXMFLOAT2(MatVec::Vector2(1.0f, 0.0f));
	((Vertex*)vertex_map_)[4].uv_ = MatVec::ConvertToXMFLOAT2(MatVec::Vector2(0.0f, 0.0f));
	index_buffer_ = game.mdx12.CreateIndexBuffer(6, L"MainSceneFlippingLayer::index_buffer_");
	auto index_map = static_cast<unsigned int*>(game.mdx12.Map(index_buffer_));
	index_map[0] = 0;
	index_map[1] = 1;
	index_map[2] = 3;
	index_map[3] = 1;
	index_map[4] = 2;
	index_map[5] = 3;
	game.mdx12.Unmap(index_buffer_);
}

double MainSceneFlippingLayer::GetRotation()
{
	double theta = 0.0;
	int t = GetLayert();
	if (t < (halfturn_time_ + stay_time_) * halfturn_num_)
	{
		t %= 2 * (halfturn_time_ + stay_time_);
		if (t < halfturn_time_)
		{
			theta = PI * t / halfturn_time_;
		}
		else if (t < halfturn_time_ + stay_time_)
		{
			theta = PI;
		}
		else if (t < 2 * halfturn_time_ + stay_time_)
		{
			theta = PI + PI * (t - halfturn_time_ - stay_time_) / halfturn_time_;
		}
		else {
			theta = 0.0;
		}
	}
	return theta;
}

const int MainSceneFlippingLayer::halfturn_time_ = 60;
const int MainSceneFlippingLayer::stay_time_ = 240;
const int MainSceneFlippingLayer::halfturn_num_ = 6;

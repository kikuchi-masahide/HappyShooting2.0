#include "MainSceneTackledLayer.h"

#include "Boss2State2.h"
#include "../Engine/Scene.h"

namespace {
	struct Vertex {
	public:
		XMFLOAT3 pos_;
		XMFLOAT2 uv_;
	};
}

MainSceneTackledLayer::MainSceneTackledLayer(Scene* scene, DrawComponentsMultiset* draw_components)
	:MainSceneBaseLayer(scene,draw_components),
	x_(MatVec::Vector2()),v_(MatVec::Vector2()),frame_(scene->mGame)
{
	GraphicsInit(scene->mGame);
	verts_temp_[0] = MatVec::Vector4(-450.0, +450.0, 0.0, 1.0);
	verts_temp_[1] = MatVec::Vector4(-450.0, -450.0, 0.0, 1.0);
	verts_temp_[2] = MatVec::Vector4(+150.0, -450.0, 0.0, 1.0);
	verts_temp_[3] = MatVec::Vector4(+150.0, +450.0, 0.0, 1.0);
	conv_ = MatVec::GetOrthoGraphicProjection(900.0, 900.0, 0.0, 1.0);
}

MainSceneTackledLayer::~MainSceneTackledLayer()
{
}

void MainSceneTackledLayer::UniqueDraw()
{
	int t = GetLayert();
	if (t < 570) {
		//x_,v_の更新
		x_ += v_ / 60;
		//v'を求める
		MatVec::Vector2 vv = v_;
		if (x_.Norm2() > 1e-6)
		{
			vv = MatVec::Dot(x_, v_) * x_ / x_.Norm2();
		}
		//外力
		MatVec::Vector2 F(0.0, 0.0);
		//timetable_[n].time_ == tなるnを探す
		int n = 0;
		for (; n < 16; n++)
		{
			if (Boss2State2::timetable_[n].time_ == t)
			{
				break;
			}
		}
		//timetable_[n].time_ == tとなる場合
		if (n != 16)
		{
			auto pn = Boss2State2::timetable_[n - 1].pos_;
			auto pnn = Boss2State2::timetable_[n].pos_;
			if (abs(pnn(0)) >= 300 - 50.0 || abs(pnn(1)) >= 450 - 50.0) {
				//カベにぶつかっている場合、移動方向を求める(正規化)
				auto delta = pnn - pn;
				delta.Normalize();
				F = delta * abs_f_;
			}
		}
		MatVec::Vector2 a = F - spring_const_ * vv;
		v_ += a / 60;
		x_570_ = x_;
	}
	//いつまでもびよんびよんして戻らないので、強制的に戻す
	else {
		x_ -= x_570_ / 60;
	}
	for (int n = 0; n < 4; n++)
	{
		auto v = verts_temp_[n] + MatVec::Vector4(x_(0), x_(1), 0.0, 0.0);
		v = conv_ * v;
		((Vertex*)verts_map_)[n].pos_ = MatVec::ConvertToXMFLOAT3(MatVec::Vector3(v(0), v(1), v(2)));
	}
	auto& game = GetGame();
	game.OpenSwapChain(0);
	game.mdx12.SetGraphicsPipeline(pipeline_);
	game.mdx12.SetRootSignature(root_signature_);
	game.mdx12.SetDescriptorHeap(pera_srv_);
	game.mdx12.SetGraphicsRootDescriptorTable(0, pera_srv_, 0);
	game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLELIST);
	game.mdx12.SetVertexBuffers(vertex_buffer_,0,sizeof(Vertex)*4,sizeof(Vertex));
	game.mdx12.SetIndexBuffers(index_buffer_,6);
	game.mdx12.SetViewports(900, 900, 0, 0, 1.0f, 0.0f);
	game.mdx12.SetScissorrect(0, 900, 0, 600);
	game.mdx12.DrawIndexedInstanced(6, 1, 0, 0, 0);
	frame_.DrawFrame(game, -150.0 + x_(0), 0.0 + x_(1), 600.0, 900.0, 0.0, 900.0, 900.0);
	game.CloseSwapChain();
}

MatVec::Matrix4x4 MainSceneTackledLayer::GetLayerTransform()
{
	return MatVec::Identity4x4();
}

void MainSceneTackledLayer::GraphicsInit(Game& game)
{
	auto vertex = game.mShaderManager.GetDX12ShaderObject(2);
	auto pixel = game.mShaderManager.GetDX12ShaderObject(3);
	DX12VertexLayout vertex_layout;
	vertex_layout.push_back(DX12VertexLayoutUnit(
		"POSITION", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));
	vertex_layout.push_back(DX12VertexLayoutUnit(
		"TEXCOORD", DX12Config::VertexLayoutFormat::R32G32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));
	DX12RootParameter root_param;
	root_param.mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;
	root_param.mDescRanges.push_back(DX12DescriptorRange(1, DX12Config::DescriptorRangeType::SRV, 0, 0));
	root_signature_ = game.mdx12.CreateRootSignature(root_param);
	pipeline_ = game.mdx12.CreateGraphicsPipeline(
		vertex, pixel, vertex_layout, DX12Config::PrimitiveTopologyType::TRIANGLE, 1, root_signature_, L"MainSceneTackledLayer::pipeline_"
	);
	vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(Vertex) * 4, L"MainSceneTackledLayer::vertex_buffer_");
	verts_map_ = game.mdx12.Map(vertex_buffer_);
	//0 3
	//1 2
	((Vertex*)verts_map_)[0].uv_ = MatVec::ConvertToXMFLOAT2(MatVec::Vector2(0.0, 0.0));
	((Vertex*)verts_map_)[1].uv_ = MatVec::ConvertToXMFLOAT2(MatVec::Vector2(0.0, 1.0));
	((Vertex*)verts_map_)[2].uv_ = MatVec::ConvertToXMFLOAT2(MatVec::Vector2(1.0, 1.0));
	((Vertex*)verts_map_)[3].uv_ = MatVec::ConvertToXMFLOAT2(MatVec::Vector2(1.0, 0.0));
	index_buffer_ = game.mdx12.CreateIndexBuffer(6, L"MainSceneTackledLayer::index_buffer_");
	unsigned int* index_map = static_cast<unsigned int*>(game.mdx12.Map(index_buffer_));
	index_map[0] = 0;
	index_map[1] = 1;
	index_map[2] = 3;
	index_map[3] = 1;
	index_map[4] = 3;
	index_map[5] = 2;
	game.mdx12.Unmap(index_buffer_);
}

const double MainSceneTackledLayer::abs_f_ = 8000.0;
const double MainSceneTackledLayer::spring_const_ = 30.0;

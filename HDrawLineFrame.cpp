#include "stdafx.h"
#include "HDrawLineFrame.h"

HDrawLineFrame::HDrawLineFrame(Game& game)
{
	if (pipeline_ == nullptr)
	{
		GraphicInit(game);
	}
	//頂点バッファはstaticじゃないのでここで初期化
	vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(XMFLOAT3) * 5, L"HDrawLineFrame VertexBuffer");
	map_ = static_cast<XMFLOAT3*>(game.mdx12.Map(vertex_buffer_));
}

void HDrawLineFrame::DrawFrame(Game& game, double center_x, double center_y, double width, double height, double angle, unsigned int rt_width, unsigned int rt_height)
{
	//頂点バッファのセット
	//回転をかける前の，重心が原点と一致する，幅/高さがwidth/heightの頂点
	MatVec::Vector4 points[5];
	points[0] = MatVec::Vector4(-width / 2, +height / 2, 0, 1.0);
	points[1] = MatVec::Vector4(-width / 2, -height / 2, 0, 1.0);
	points[2] = MatVec::Vector4(+width / 2, -height / 2, 0, 1.0);
	points[3] = MatVec::Vector4(+width / 2, +height / 2, 0, 1.0);
	points[4] = MatVec::Vector4(-width / 2, +height / 2, 0, 1.0);   //頂点0に戻ってくる
	//回転行列
	MatVec::Matrix4x4 matrix = MatVec::Rotate(MatVec::GetQuaternion(
		MatVec::Vector3(0, 0, -1), angle
	));
	matrix = MatVec::Translation(center_x, center_y, 0.0)*matrix;
	matrix = MatVec::GetOrthoGraphicProjection(rt_width, rt_height, 0.0, 1.0) * matrix;
	for (unsigned int i = 0; i < 5; i++)
	{
		points[i] = matrix * points[i];
	}
	for (unsigned int i = 0; i < 5; i++)
	{
		map_[i] = MatVec::ConvertToXMFLOAT3(MatVec::XYZ(points[i]));
	}

	//パイプライン実行
	game.mdx12.SetGraphicsPipeline(pipeline_);
	game.mdx12.SetRootSignature(root_signature_);
	game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::LINESTRIP);
	game.mdx12.SetVertexBuffers(vertex_buffer_, 0, sizeof(XMFLOAT3) * 5, sizeof(XMFLOAT3));
	game.mdx12.SetViewports(rt_width, rt_height, 0, 0, 0.0f, 1.0f);
	game.mdx12.SetScissorrect(0, rt_width, 0, rt_height);
	game.mdx12.DrawInstanced(5, 1, 0, 0);
}

void HDrawLineFrame::GraphicInit(Game& game)
{
	auto vertex_shader = game.mShaderManager.GetDX12ShaderObject(4);
	auto pixel_shader = game.mShaderManager.GetDX12ShaderObject(5);

	DX12VertexLayout vertex_layout;
	vertex_layout.push_back(DX12VertexLayoutUnit(
		"POSITION", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));

	DX12RootParameter root_parameters;
	root_parameters.mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;
	root_signature_ = game.mdx12.CreateRootSignature(root_parameters,false);

	pipeline_ = game.mdx12.CreateGraphicsPipeline(
		vertex_shader, pixel_shader, vertex_layout, DX12Config::PrimitiveTopologyType::LINE, 1, root_signature_,L"HDrawLineFrame::pipeline_"
	);
}

boost::shared_ptr<DX12GraphicsPipeline> HDrawLineFrame::pipeline_ = nullptr;
boost::shared_ptr<DX12RootSignature> HDrawLineFrame::root_signature_ = nullptr;
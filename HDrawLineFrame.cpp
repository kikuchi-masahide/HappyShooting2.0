#include "stdafx.h"
#include "HDrawLineFrame.h"

HDrawLineFrame::HDrawLineFrame(Game& game)
{
	if (pipeline_ == nullptr)
	{
		GraphicInit(game);
	}
	//頂点バッファはstaticじゃないのでここで初期化
	vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(float) * 15);
}

void HDrawLineFrame::DrawFrame(Game& game, double center_x, double center_y, double width, double height, double angle, unsigned int rt_width, unsigned int rt_height)
{
	//頂点バッファのセット
	//回転をかける前の，重心が原点と一致する，幅/高さがwidth/heightの頂点
	MatVec::Vector4 points[5];
	points[0] = MatVec::Vector4(- width / 2, + height / 2, 0, 1.0);
	points[1] = MatVec::Vector4(- width / 2, - height / 2, 0, 1.0);
	points[2] = MatVec::Vector4(+ width / 2, - height / 2, 0, 1.0);
	points[3] = MatVec::Vector4(+ width / 2, + height / 2, 0, 1.0);
	points[4] = MatVec::Vector4(- width / 2, + height / 2, 0, 1.0);   //頂点0に戻ってくる
	//回転行列
	MatVec::Matrix rot = MatVec::Rotate(MatVec::GetQuaternion(
		MatVec::Vector3(0, 0, -1), angle
	));
	for (unsigned int i = 0; i < 5; i++)
	{
		points[i] = rot * points[i];
		points[i] += MatVec::Vector4(center_x, center_y, 0, 0.0);
	}
	//-1~1に変換
	for (unsigned int i = 0; i < 5; i++)
	{
		points[i] /= points[i](3);
		points[i][0] = 2 * points[i][0] / rt_width - 1;
		points[i][1] = 2 * points[i][1] / rt_height - 1;
	}
	float* map = static_cast<float*>(game.mdx12.Map(vertex_buffer_));
	for (unsigned int i = 0; i < 5; i++) {
		map[3 * i + 0] = points[i](0);
		map[3 * i + 1] = points[i](1);
		map[3 * i + 2] = points[i](2);
	}
	game.mdx12.Unmap(vertex_buffer_);

	//パイプライン実行
	game.mdx12.SetGraphicsPipeline(pipeline_);
	game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::LINESTRIP);
	game.mdx12.SetVertexBuffers(vertex_buffer_,0,sizeof(float)*15,sizeof(float)*3);
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

	std::vector<DX12RootParameter> root_parameters;
	root_signature_ = game.mdx12.CreateRootSignature(root_parameters);

	pipeline_ = game.mdx12.CreateGraphicsPipeline(
		vertex_shader, pixel_shader, vertex_layout, DX12Config::PrimitiveTopologyType::LINE, 1, root_signature_
	);
}

boost::shared_ptr<DX12GraphicsPipeline> HDrawLineFrame::pipeline_ = nullptr;
boost::shared_ptr<DX12RootSignature> HDrawLineFrame::root_signature_ = nullptr;
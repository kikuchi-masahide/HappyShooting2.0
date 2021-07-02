#include "stdafx.h"
#include "HTextureAlphaRotateDraw.h"

HTextureAlphaRotateDraw::HTextureAlphaRotateDraw(Game& game, unsigned int textureid)
{
	//通算1つ目のインスタンス
	if (info_to_shader_ == nullptr)
	{
		StaticGraphicInit(game);
	}
	texture_id_ = textureid;
	NonstaticGraphicsInit(game);
}

void HTextureAlphaRotateDraw::Draw(Game& game, double center_x, double center_y, double width, double height, double angle, double alpha, double rt_width, double rt_height)
{
	//シェーダーに渡す情報
	*alpha_map_ = alpha;

	//頂点座標を変化させる
	//(シェーダに行列を渡すとなぜか正方形が歪んだので)
	MatVec::Matrix4x4 matrix = MatVec::Rotate(MatVec::GetQuaternion(
		MatVec::Vector3(0, 0, 1), -angle
	));
	matrix = MatVec::Translation(MatVec::Vector3(center_x, center_y, 0))*matrix;
	matrix = MatVec::GetOrthoGraphicProjection(rt_width, rt_height, 0.0, 1.0)*matrix;
	MatVec::Vector4 points_before[4];
	points_before[0] = MatVec::Vector4(-width / 2, height / 2, 0.0, 1.0);
	points_before[1] = MatVec::Vector4(-width / 2, -height / 2, 0.0, 1.0);
	points_before[2] = MatVec::Vector4(width / 2, -height / 2, 0.0, 1.0);
	points_before[3] = MatVec::Vector4(width / 2, height / 2, 0.0, 1.0);
	for (unsigned int n = 0; n < 4; n++)
	{
		points_before[n] = matrix * points_before[n];
		vertexs_[n].pos_ = MatVec::ConvertToXMFLOAT3(MatVec::XYZ(points_before[n]));
	}
	void* map_pointer = game.mdx12.Map(vertex_buffer_);
	std::memcpy(map_pointer, vertexs_, sizeof(vertexs_));
	game.mdx12.Unmap(vertex_buffer_);

	//パイプライン実行
	game.mdx12.SetGraphicsPipeline(graphics_pipeline_);
	game.mdx12.SetRootSignature(rootsignature_);
	game.mdx12.SetDescriptorHeap(srv_heap_);
	game.mdx12.SetGraphicsRootDescriptorTable(0, srv_heap_, srv_heap_ind_);
	game.mdx12.SetDescriptorHeap(info_crv_heap_);
	game.mdx12.SetGraphicsRootDescriptorTable(1, info_crv_heap_, 0);
	game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLELIST);
	game.mdx12.SetVertexBuffers(vertex_buffer_, 0, sizeof(Vertex) * 4, sizeof(Vertex));
	game.mdx12.SetIndexBuffers(index_buffer_, 6);
	game.mdx12.SetViewports(rt_width, rt_height, 0, 0, 1.0f, 0.0f);
	game.mdx12.SetScissorrect(0, rt_height, 0, rt_width);
	game.mdx12.DrawIndexedInstanced(6, 1, 0, 0, 0);
}

void HTextureAlphaRotateDraw::StaticGraphicInit(Game& game)
{
	//ルートパラメタ0:
	//	レンジ0:SRV,t0~t0 <---> テクスチャのヒープ
	//
	//ルートパラメタ1:
	//	レンジ0:CRV,b0~b0 <---> info_crv_heap_
	std::vector<DX12RootParameter> root_params(2);
	root_params[0].mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;
	root_params[0].mDescRanges.push_back(DX12DescriptorRange(
		1, DX12Config::DescriptorRangeType::SRV, 0, 0
	));
	root_params[1].mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;
	root_params[1].mDescRanges.push_back(DX12DescriptorRange(
		1, DX12Config::DescriptorRangeType::CBV, 0, 0
	));
	rootsignature_ = game.mdx12.CreateRootSignature(root_params);

	//インデックスバッファ
	index_buffer_ = game.mdx12.CreateIndexBuffer(6);
	unsigned int* indexmap = static_cast<unsigned int*>(game.mdx12.Map(index_buffer_));
	//0 3
	//1 2
	indexmap[0] = 0;
	indexmap[1] = 1;
	indexmap[2] = 3;
	indexmap[3] = 1;
	indexmap[4] = 2;
	indexmap[5] = 3;
	game.mdx12.Unmap(index_buffer_);

	//シェーダー取得
	auto vertexshader = game.mShaderManager.GetDX12ShaderObject(6);
	auto pixelshader = game.mShaderManager.GetDX12ShaderObject(7);

	//頂点レイアウト
	DX12VertexLayout vertexlayout;
	vertexlayout.push_back(DX12VertexLayoutUnit(
		"POSITION", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));
	vertexlayout.push_back(DX12VertexLayoutUnit(
		"TEXCOORD", DX12Config::VertexLayoutFormat::R32G32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));

	//パイプライン作成
	graphics_pipeline_ = game.mdx12.CreateGraphicsPipeline(
		vertexshader, pixelshader, vertexlayout, DX12Config::PrimitiveTopologyType::TRIANGLE, 1, rootsignature_
	);
}

void HTextureAlphaRotateDraw::NonstaticGraphicsInit(Game& game)
{
	//定数バッファ初期化
	info_to_shader_ = game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD, sizeof(float));
	info_crv_heap_ = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 1);
	game.mdx12.CreateConstBufferView(info_to_shader_, info_crv_heap_, 0);
	alpha_map_ = static_cast<float*>(game.mdx12.Map(info_to_shader_));

	//頂点情報
	vertexs_[0].uv_ = XMFLOAT2(0.0f, 0.0f);
	vertexs_[1].uv_ = XMFLOAT2(0.0f, 1.0f);
	vertexs_[2].uv_ = XMFLOAT2(1.0f, 1.0f);
	vertexs_[3].uv_ = XMFLOAT2(1.0f, 0.0f);


	//頂点バッファ作成
	vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(Vertex) * 4);

	//テクスチャsrv読み込み
	auto res = game.mTexManager.GetDX12DescriptorHeap(texture_id_);
	srv_heap_ = res.first;
	srv_heap_ind_ = res.second;
}

boost::shared_ptr<DX12GraphicsPipeline> HTextureAlphaRotateDraw::graphics_pipeline_ = nullptr;
boost::shared_ptr<DX12RootSignature> HTextureAlphaRotateDraw::rootsignature_ = nullptr;
boost::shared_ptr<DX12Resource> HTextureAlphaRotateDraw::index_buffer_ = nullptr;
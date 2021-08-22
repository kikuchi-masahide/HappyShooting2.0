#include "stdafx.h"
#include "HDrawLineFrame.h"

namespace {
	struct InfoToShader {
	public:
		XMMATRIX conv_;
		XMFLOAT3 color_;
		float alpha_;
	};
}

namespace Helpers {

	HDrawLineFrame::HDrawLineFrame(Game& game)
		:map_(nullptr)
	{
		if (pipeline_ == nullptr)
		{
			StaticGraphicInit(game);
		}
		const_buffer_ = game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD, sizeof(InfoToShader), L"HDrawLineFrame::const_buffer_");
		crv_heap_ = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 1, L"HDrawLineFrame::crv_heap_");
		game.mdx12.CreateConstBufferView(const_buffer_, crv_heap_, 0);
		map_ = game.mdx12.Map(const_buffer_);
	}

	void HDrawLineFrame::DrawFrame(Game& game, double center_x, double center_y, double width, double height, double angle, unsigned int rt_width, unsigned int rt_height, MatVec::Vector4 color)
	{
		//回転行列
		MatVec::Matrix4x4 matrix = MatVec::Expand(width, height, 1.0);
		matrix = MatVec::Rotate(MatVec::GetQuaternion(
			MatVec::Vector3(0, 0, -1), angle
		)) * matrix;
		matrix = MatVec::Translation(center_x, center_y, 0.0) * matrix;
		matrix = MatVec::GetOrthoGraphicProjection(rt_width, rt_height, 0.0, 1.0) * matrix;
		InfoToShader* info_map = static_cast<InfoToShader*>(map_);
		info_map->conv_ = MatVec::ConvertToXMMATRIX(matrix);
		info_map->color_ = MatVec::ConvertToXMFLOAT3(MatVec::XYZ(color));
		info_map->alpha_ = static_cast<float>(color(3));

		//パイプライン実行
		game.mdx12.SetGraphicsPipeline(pipeline_);
		game.mdx12.SetRootSignature(root_signature_);
		game.mdx12.SetDescriptorHeap(crv_heap_);
		game.mdx12.SetGraphicsRootDescriptorTable(0, crv_heap_, 0);
		game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::LINESTRIP);
		game.mdx12.SetVertexBuffers(vertex_buffer_, 0, sizeof(XMFLOAT3) * 5, sizeof(XMFLOAT3));
		game.mdx12.SetViewports(rt_width, rt_height, 0, 0, 0.0f, 1.0f);
		game.mdx12.SetScissorrect(0, rt_width, 0, rt_height);
		game.mdx12.DrawInstanced(5, 1, 0, 0);
	}

	void HDrawLineFrame::StaticGraphicInit(Game& game)
	{
		auto vertex_shader = game.mShaderManager.GetDX12ShaderObject(4);
		auto pixel_shader = game.mShaderManager.GetDX12ShaderObject(5);

		DX12VertexLayout vertex_layout;
		vertex_layout.push_back(DX12VertexLayoutUnit(
			"POSITION", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		));

		DX12RootParameter root_parameters;
		root_parameters.mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;
		root_parameters.mDescRanges.push_back(DX12DescriptorRange(1, DX12Config::DescriptorRangeType::CBV, 0, 0));
		root_signature_ = game.mdx12.CreateRootSignature(root_parameters, false);

		pipeline_ = game.mdx12.CreateGraphicsPipeline(
			vertex_shader, pixel_shader, vertex_layout, DX12Config::PrimitiveTopologyType::LINE, 1, root_signature_, L"HDrawLineFrame::pipeline_"
		);

		vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(XMFLOAT3) * 5, L"HDrawLineFrame::vertex_buffer_");
		XMFLOAT3* vertex_map = static_cast<XMFLOAT3*>(game.mdx12.Map(vertex_buffer_));
		vertex_map[0] = XMFLOAT3(-0.5f, +0.5f, 0.0f);
		vertex_map[1] = XMFLOAT3(-0.5f, -0.5f, 0.0f);
		vertex_map[2] = XMFLOAT3(+0.5f, -0.5f, 0.0f);
		vertex_map[3] = XMFLOAT3(+0.5f, +0.5f, 0.0f);
		vertex_map[4] = XMFLOAT3(-0.5f, +0.5f, 0.0f);   //頂点0に戻ってくる
		game.mdx12.Unmap(vertex_buffer_);
	}

	boost::shared_ptr<DX12GraphicsPipeline> HDrawLineFrame::pipeline_ = nullptr;
	boost::shared_ptr<DX12RootSignature> HDrawLineFrame::root_signature_ = nullptr;
	boost::shared_ptr<DX12Resource> HDrawLineFrame::vertex_buffer_ = nullptr;
}
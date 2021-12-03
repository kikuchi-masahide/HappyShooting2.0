#include "HSquareRepeatPattern.h"

namespace {
	struct Vertex
	{
	public:
		XMFLOAT3 pos_;
		XMFLOAT2 uv_;
	};
	struct InfoToShader
	{
	public:
		XMMATRIX mat_;
		float alpha_;
	};
}

namespace Helpers {

	HSquareRepeatPattern::HSquareRepeatPattern(Game& game, unsigned int texture_id, double texture_width, double texture_height)
		:texture_id_(texture_id), texture_width_(texture_width), texture_height_(texture_height)
	{
		if (graphics_pipeline_ == nullptr)
		{
			StaticGraphicInit(game);
		}
		NonstaticGraphicInit(game);
	}

	HSquareRepeatPattern::~HSquareRepeatPattern()
	{
	}

	void HSquareRepeatPattern::Draw(Game& game, MatVec::Vector2 center, double square_width, double square_height, double alpha, double rt_width, double rt_height)
	{
		double uv_width = square_width / texture_width_;
		double uv_height = square_height / texture_height_;
		Vertex* vertex = static_cast<Vertex*>(vertex_map_);
		vertex[0].uv_ = XMFLOAT2(0.0,0.0);
		vertex[1].uv_ = XMFLOAT2(0.0, uv_height);
		vertex[2].uv_ = XMFLOAT2(uv_width, uv_height);
		vertex[3].uv_ = XMFLOAT2(uv_width, 0.0);
		MatVec::Matrix4x4 mat = MatVec::Translation(center(0), center(1), 0.0) * MatVec::Expand(square_width, square_height, 1.0);
		mat = MatVec::GetOrthoGraphicProjection(rt_width, rt_height, 0.0, 1.0) * mat;
		InfoToShader* cbufmap = static_cast<InfoToShader*>(cbuffer_map_);
		cbufmap->mat_ = MatVec::ConvertToXMMATRIX(mat);
		cbufmap->alpha_ = alpha;

		game.mdx12.SetGraphicsPipeline(graphics_pipeline_);
		game.mdx12.SetRootSignature(root_signature_);
		game.mdx12.SetDescriptorHeap(desc_heap_);
		game.mdx12.SetGraphicsRootDescriptorTable(0, desc_heap_, 0);
		game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLELIST);
		game.mdx12.SetVertexBuffers(vertex_buffer_, 0, sizeof(Vertex) * 4, sizeof(Vertex));
		game.mdx12.SetIndexBuffers(index_buffer_, 6);
		game.mdx12.SetViewports(rt_width, rt_height, 0, 0, 1.0f, 0.0f);
		game.mdx12.SetScissorrect(0, rt_height, 0, rt_width);
		game.mdx12.DrawIndexedInstanced(6, 1, 0, 0, 0);
	}

	void HSquareRepeatPattern::StaticGraphicInit(Game& game)
	{
		//シェーダはHTextureAlphaRotateDrawを流用
		auto vsh = game.mShaderManager.GetDX12ShaderObject(6);
		auto psh = game.mShaderManager.GetDX12ShaderObject(7);

		DX12VertexLayout vertex_layout;
		vertex_layout.push_back(DX12VertexLayoutUnit(
			"POSITION", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		));
		vertex_layout.push_back(DX12VertexLayoutUnit(
			"TEXCOORD", DX12Config::VertexLayoutFormat::R32G32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		));

		DX12RootParameter root_param;
		root_param.mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;
		//0:SRV 1:CBV
		root_param.mDescRanges.push_back(DX12DescriptorRange(1, DX12Config::DescriptorRangeType::SRV, 0, 0));
		root_param.mDescRanges.push_back(DX12DescriptorRange(1, DX12Config::DescriptorRangeType::CBV, 0, 0));
		root_signature_ = game.mdx12.CreateRootSignature(root_param, true);

		graphics_pipeline_ = game.mdx12.CreateGraphicsPipeline(
			vsh, psh, vertex_layout, DX12Config::PrimitiveTopologyType::TRIANGLE, 1, root_signature_, L"HSquareRepeatPattern::graphics_pipeline"
		);

		index_buffer_ = game.mdx12.CreateIndexBuffer(6, L"HSquareRepeatPattern::index_buffer_");
		unsigned int* index_map = static_cast<unsigned int*>(game.mdx12.Map(index_buffer_));
		index_map[0] = 0;
		index_map[1] = 1;
		index_map[2] = 3;
		index_map[3] = 1;
		index_map[4] = 2;
		index_map[5] = 3;
		game.mdx12.Unmap(index_buffer_);
	}

	void HSquareRepeatPattern::NonstaticGraphicInit(Game& game)
	{
		vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(Vertex) * 4, L"HSquareRepeatPattern::vertex_buffer_");
		Vertex* vertex = static_cast<Vertex*>(game.mdx12.Map(vertex_buffer_));
		vertex[0].pos_ = XMFLOAT3(-0.5, +0.5, 0.0);
		vertex[1].pos_ = XMFLOAT3(-0.5, -0.5, 0.0);
		vertex[2].pos_ = XMFLOAT3(+0.5, -0.5, 0.0);
		vertex[3].pos_ = XMFLOAT3(+0.5, +0.5, 0.0);
		vertex_map_ = static_cast<void*>(vertex);

		const_buffer_ = game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD, sizeof(InfoToShader), L"HSquareRepeatPattern::const_buffer_");
		cbuffer_map_ = game.mdx12.Map(const_buffer_);

		desc_heap_ = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 2, L"HSquareRepeatPattern::desc_heap_");
		game.mTexManager.CreateSRVof(texture_id_, desc_heap_, 0);
		game.mdx12.CreateConstBufferView(const_buffer_, desc_heap_, 1);
	}

	boost::shared_ptr<DX12GraphicsPipeline> HSquareRepeatPattern::graphics_pipeline_ = nullptr;
	boost::shared_ptr<DX12RootSignature> HSquareRepeatPattern::root_signature_ = nullptr;
	boost::shared_ptr<DX12Resource> HSquareRepeatPattern::index_buffer_ = nullptr;
}
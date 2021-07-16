#include "stdafx.h"
#include "HNumberDraw.h"

namespace Helpers {

	namespace {
		struct Vertex {
		public:
			XMFLOAT3 pos;
			XMFLOAT2 uv;
			//左から何枚目の枠の頂点か
			unsigned int pos_left;
		};
		struct InfoToShader {
		public:
			XMMATRIX matrix;
			unsigned int numbers[8];
		};
	}

	HNumberDraw::HNumberDraw(Game& game, double font_size, MatVec::Vector2 leftup_position, unsigned int rt_width, unsigned int rt_height, unsigned int max_digit)
		:font_size_(font_size), leftup_position_(leftup_position), rt_width_(rt_width), rt_height_(rt_height), max_digit_(min(max_digit, 8))
	{
		if (pipeline_ == nullptr)
		{
			StaticGraphicInit(game);
		}
		NonstaticGraphicInit(game);
	}

	HNumberDraw::~HNumberDraw()
	{
	}

	void HNumberDraw::DrawNumber(Game& game, int number)
	{
		//表示すべき数
		std::vector<unsigned int> outputs;
		if (number < 0)
		{
			//負の数なので-を先頭に置く
			outputs.push_back(10);
			number *= -1;
		}
		//numberの絶対の10進表示(逆順)
		std::vector<unsigned int> digits_inv;
		if (number == 0) {
			digits_inv.push_back(0);
		}
		else {
			while (number > 0)
			{
				digits_inv.push_back(number % 10);
				number /= 10;
			}
		}
		//数字をoutputsに入れきるか，outputsが容量いっぱいになるまで追加
		while (digits_inv.size() > 0 && outputs.size() < max_digit_)
		{
			outputs.push_back(digits_inv.back());
			digits_inv.pop_back();
		}
		//numberを入れてまだスペースがあれば空白を追加
		while (outputs.size() < max_digit_)
		{
			outputs.push_back(11);
		}

		//変換行列を求める
		//画像は縦:横=40:24=5:3
		MatVec::Matrix4x4 matrix =
			MatVec::GetOrthoGraphicProjection(rt_width_, rt_height_, 0.0, 1.0) *
			MatVec::Translation(MatVec::XY0(leftup_position_)) *
			MatVec::Expand(font_size_ * 0.6, font_size_, 1.0);
		InfoToShader* info_map = static_cast<InfoToShader*>(const_map_);
		info_map->matrix = MatVec::ConvertToXMMATRIX(matrix);
		for (unsigned int i = 0; i < max_digit_; i++)
		{
			info_map->numbers[i] = outputs[i];
		}

		game.mdx12.SetGraphicsPipeline(pipeline_);
		game.mdx12.SetRootSignature(root_signature_);
		game.mdx12.SetDescriptorHeap(desc_heap_);
		game.mdx12.SetGraphicsRootDescriptorTable(0, desc_heap_, 0);
		game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLELIST);
		game.mdx12.SetVertexBuffers(vertex_buffer_, 0, sizeof(Vertex) * 4 * max_digit_, sizeof(Vertex));
		game.mdx12.SetIndexBuffers(index_buffer_, 6 * max_digit_);
		game.mdx12.SetViewports(rt_width_, rt_height_, 0, 0, 1.0f, 0.0f);
		game.mdx12.SetScissorrect(0, rt_height_, 0, rt_width_);
		game.mdx12.DrawIndexedInstanced(6 * max_digit_, 1, 0, 0, 0);
	}

	void HNumberDraw::StaticGraphicInit(Game& game)
	{
		auto vertex_shader = game.mShaderManager.GetDX12ShaderObject(10);
		auto pixel_shader = game.mShaderManager.GetDX12ShaderObject(11);

		DX12VertexLayout vertex_layout;
		vertex_layout.push_back(DX12VertexLayoutUnit(
			"POSITION", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		));
		vertex_layout.push_back(DX12VertexLayoutUnit(
			"TEXCOORD", DX12Config::VertexLayoutFormat::R32G32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		));
		vertex_layout.push_back(DX12VertexLayoutUnit(
			"LEFT_INDEX", DX12Config::VertexLayoutFormat::R32_UINT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
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

		pipeline_ = game.mdx12.CreateGraphicsPipeline(
			vertex_shader, pixel_shader, vertex_layout,
			DX12Config::PrimitiveTopologyType::TRIANGLE, 1, root_signature_, L"HNumberDraw::pipeline_"
		);
	}

	void HNumberDraw::NonstaticGraphicInit(Game& game)
	{
		//インデックスバッファ
		index_buffer_ = game.mdx12.CreateIndexBuffer(6 * max_digit_, L"HNumberDraw::index_buffer_");
		unsigned int* index_map = static_cast<unsigned int*>(game.mdx12.Map(index_buffer_));
		//0個目の枠
		index_map[0] = 0;
		index_map[1] = 1;
		index_map[2] = 3;
		index_map[3] = 1;
		index_map[4] = 2;
		index_map[5] = 3;
		//1個目以降は前のに+4するだけ
		for (unsigned int digit = 1, index = 6; digit < max_digit_; digit++)
		{
			for (unsigned int i = 0; i < 6; i++, index++)
			{
				index_map[index] = index_map[index - 6] + 4;
			}
		}
		game.mdx12.Unmap(index_buffer_);

		//頂点バッファ
		vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(Vertex) * 4 * max_digit_, L"HNumberDraw::vertex_buffer_");
		Vertex* vertex_array = static_cast<Vertex*>(game.mdx12.Map(vertex_buffer_));
		for (unsigned int index = 0; index < max_digit_; index++)
		{
			//0 3
			//1 2
			vertex_array[4 * index + 0].pos = XMFLOAT3(index + 0, +0.0, 0.0);
			vertex_array[4 * index + 1].pos = XMFLOAT3(index + 0, -1.0, 0.0);
			vertex_array[4 * index + 2].pos = XMFLOAT3(index + 1, -1.0, 0.0);
			vertex_array[4 * index + 3].pos = XMFLOAT3(index + 1, +0.0, 0.0);

			vertex_array[4 * index + 0].uv = XMFLOAT2(0.0, 0.0);
			vertex_array[4 * index + 1].uv = XMFLOAT2(0.0, 1.0);
			vertex_array[4 * index + 2].uv = XMFLOAT2(1.0, 1.0);
			vertex_array[4 * index + 3].uv = XMFLOAT2(1.0, 0.0);

			vertex_array[4 * index + 0].pos_left = index;
			vertex_array[4 * index + 1].pos_left = index;
			vertex_array[4 * index + 2].pos_left = index;
			vertex_array[4 * index + 3].pos_left = index;
		}
		game.mdx12.Unmap(vertex_buffer_);

		const_buffer_ = game.mdx12.CreateConstBuffer(
			DX12Config::ResourceHeapType::UPLOAD, sizeof(InfoToShader), L"HNumberDraw::const_buffer_"
		);
		const_map_ = game.mdx12.Map(const_buffer_);

		//ディスクリプタヒープ，SRV，CRV
		desc_heap_ = game.mdx12.CreateDescriptorHeap(
			DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 2, L"HNumberDraw::desc_heap_"
		);
		game.mTexManager.CreateSRVof(6, desc_heap_, 0);
		game.mdx12.CreateConstBufferView(const_buffer_, desc_heap_, 1);
	}

	boost::shared_ptr<DX12GraphicsPipeline> HNumberDraw::pipeline_ = nullptr;
	boost::shared_ptr<DX12RootSignature> HNumberDraw::root_signature_ = nullptr;

}
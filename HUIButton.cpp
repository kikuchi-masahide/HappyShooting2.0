#include "stdafx.h"
#include "HUIButton.h"

#include "UIScreen.h"
#include "Scene.h"

using namespace Helpers;

namespace {
	struct Vertex {
	public:
		XMFLOAT3 pos_;
		XMFLOAT2 uv_;
	};
	struct InfoToShader {
	public:
		XMMATRIX matrix;
	};
}

HUIButton::HUIButton(UIScreen* screen, unsigned int texture_away, unsigned int texture_over, double centerx, double width, double centery, double height, std::function<void(HUIButton* button)> action)
	:screen_(screen),centerx_(centerx),centery_(centery),width_(width),height_(height),click_action_(action)
{
	Game& game = screen_->mScene->mGame;
	if (pipeline_ == nullptr)
	{
		StaticGraphicInit(game);
	}
	NonstaticGraphicInit(game,texture_away,texture_over);
}

HUIButton::~HUIButton()
{
}

void HUIButton::Update()
{
	auto mousepos = screen_->mScene->GetMouseClientPos(0);
	double mousex = mousepos(0) - 450.0;
	double mousey = mousepos(1) - 450.0;
	if (
		mousex >= centerx_-width_/2 && mousex <= centerx_+width_/2 &&
		mousey >= centery_-height_/2 && mousey <= centery_+height_/2
		)
	{
		is_mouse_over_ = true;
	}
	else {
		is_mouse_over_ = false;
	}
	if (is_mouse_over_)
	{
		auto leftbutton = screen_->mScene->GetKeyState(VK_LBUTTON);
		if (leftbutton == ButtonState::Released)
		{
			click_action_(this);
		}
	}
}

void HUIButton::Output()
{
	Game& game = screen_->mScene->mGame;
	game.mdx12.SetGraphicsPipeline(pipeline_);
	game.mdx12.SetRootSignature(root_signature_);
	if (is_mouse_over_)
	{
		game.mdx12.SetDescriptorHeap(descheap_over_);
		game.mdx12.SetGraphicsRootDescriptorTable(0, descheap_over_, 0);
	}
	else {
		game.mdx12.SetDescriptorHeap(descheap_away_);
		game.mdx12.SetGraphicsRootDescriptorTable(0, descheap_away_, 0);
	}
	game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLELIST);
	game.mdx12.SetVertexBuffers(vertex_buffer_, 0, sizeof(Vertex) * 4, sizeof(Vertex));
	game.mdx12.SetIndexBuffers(index_buffer_, 6);
	game.mdx12.SetViewports(900, 900, 0, 0, 0.0f, 1.0f);
	game.mdx12.SetScissorrect(0.0f, 900.0f, 0.0f, 900.0f);
	game.mdx12.DrawIndexedInstanced(6, 1, 0, 0, 0);
}

void HUIButton::StaticGraphicInit(Game& game)
{
	//シェーダは流用
	auto vertex = game.mShaderManager.GetDX12ShaderObject(0);
	auto pixel = game.mShaderManager.GetDX12ShaderObject(1);

	DX12VertexLayout vertex_layout;
	vertex_layout.push_back(DX12VertexLayoutUnit(
		"POSITION", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0)
	);
	vertex_layout.push_back(DX12VertexLayoutUnit(
		"TEXCOORD", DX12Config::VertexLayoutFormat::R32G32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));

	DX12RootParameter root_param;
	root_param.mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;
	root_param.mDescRanges.push_back(DX12DescriptorRange(
		1, DX12Config::DescriptorRangeType::CBV, 0, 0
	));
	root_param.mDescRanges.push_back(DX12DescriptorRange(
		1, DX12Config::DescriptorRangeType::SRV, 0, 0
	));
	root_signature_ = game.mdx12.CreateRootSignature(root_param);

	pipeline_ = game.mdx12.CreateGraphicsPipeline(
		vertex, pixel, vertex_layout, DX12Config::PrimitiveTopologyType::TRIANGLE, 1, root_signature_, L"HUIButton::pipeline_"
	);

	vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(Vertex) * 4, L"HUIButton::vertex_buffer_");
	Vertex* vertex_map = static_cast<Vertex*>(game.mdx12.Map(vertex_buffer_));
	vertex_map[0].pos_ = XMFLOAT3(-0.5f, +0.5f, 0.0f);
	vertex_map[1].pos_ = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	vertex_map[2].pos_ = XMFLOAT3(+0.5f, -0.5f, 0.0f);
	vertex_map[3].pos_ = XMFLOAT3(+0.5f, +0.5f, 0.0f);
	vertex_map[0].uv_ = XMFLOAT2(0.0f, 0.0f);
	vertex_map[1].uv_ = XMFLOAT2(0.0f, 1.0f);
	vertex_map[2].uv_ = XMFLOAT2(1.0f, 1.0f);
	vertex_map[3].uv_ = XMFLOAT2(1.0f, 0.0f);
	game.mdx12.Unmap(vertex_buffer_);

	index_buffer_ = game.mdx12.CreateIndexBuffer(6, L"HUIButton::index_buffer_");
	unsigned int* index_map = static_cast<unsigned int*>(game.mdx12.Map(index_buffer_));
	index_map[0] = 0;
	index_map[1] = 1;
	index_map[2] = 3;
	index_map[3] = 1;
	index_map[4] = 2;
	index_map[5] = 3;
	game.mdx12.Unmap(index_buffer_);
}

void HUIButton::NonstaticGraphicInit(Game& game, unsigned int texture_away, unsigned int texture_over)
{
	const_buffer_ = game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD, sizeof(InfoToShader), L"HUIButton::const_buffer_");
	InfoToShader* const_map = static_cast<InfoToShader*>(game.mdx12.Map(const_buffer_));
	MatVec::Matrix4x4 matrix = MatVec::Translation(centerx_,centery_, 0.0)*MatVec::Expand(width_,height_,1.0);
	matrix = MatVec::GetOrthoGraphicProjection(900.0, 900.0, 0.0,1.0)*matrix;
	const_map->matrix = MatVec::ConvertToXMMATRIX(matrix);
	game.mdx12.Unmap(const_buffer_);

	descheap_away_ = game.mdx12.CreateDescriptorHeap(
		DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 2, L"HUIButton::descheap_away_"
	);
	game.mdx12.CreateConstBufferView(const_buffer_, descheap_away_, 0);
	game.mTexManager.CreateSRVof(texture_away, descheap_away_, 1);

	descheap_over_ = game.mdx12.CreateDescriptorHeap(
		DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 2, L"HUIButton::descheap_over_"
	);
	game.mdx12.CreateConstBufferView(const_buffer_, descheap_over_, 0);
	game.mTexManager.CreateSRVof(texture_over, descheap_over_, 1);
}

boost::shared_ptr<DX12GraphicsPipeline> HUIButton::pipeline_ = nullptr;
boost::shared_ptr<DX12RootSignature> HUIButton::root_signature_ = nullptr;
boost::shared_ptr<DX12Resource> HUIButton::vertex_buffer_ = nullptr;
boost::shared_ptr<DX12Resource> HUIButton::index_buffer_ = nullptr;
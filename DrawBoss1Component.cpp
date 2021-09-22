#include "stdafx.h"
#include "DrawBoss1Component.h"

#include "GameObject.h"
#include "Scene.h"

namespace {
	struct InfoToShader {
	public:
		XMMATRIX conv_;
		XMFLOAT3 color_;
		float alpha_;
	};
}

DrawBoss1Component::DrawBoss1Component(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, double z)
	:MainSceneDrawComponent(object, layer_manager, z),
	t_(-1)
{
	GraphicsInit();
}

DrawBoss1Component::~DrawBoss1Component()
{
}

void DrawBoss1Component::Draw()
{
	//回転角度
	double deg = delta_theta_ * t_;
	//四角形を中心からどれだけ離すか
	double w = square_w_ * (cos(deg) + 1) / 2;
	auto& game = mObj->mScene->mGame;
	game.mdx12.SetGraphicsPipeline(graphics_pipeline_);
	game.mdx12.SetRootSignature(root_signature_);
	game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::LINESTRIP);
	game.mdx12.SetVertexBuffers(vertex_buffer_,0,sizeof(XMFLOAT3)*5,sizeof(XMFLOAT3));
	game.mdx12.SetViewports(600, 900, 0, 0, 0.0f, 1.0f);
	game.mdx12.SetScissorrect(0.0f, 900.0f, 0.0f, 600.0f);
	for (int i = 0; i < 4; i++)
	{
		MatVec::Matrix4x4 mat = MatVec::Translation(w, 0.0, 0.0);
		mat = MatVec::Rotate(MatVec::GetQuaternion(MatVec::Vector3(0.0, 0.0, 1.0), deg+ PI*i/2)) * mat;
		mat = MatVec::GetOrthoGraphicProjection(600.0, 900.0, 0.0, 1.0) * mat;
		static_cast<InfoToShader*>(const_map_[i])->conv_ = MatVec::ConvertToXMMATRIX(mat);
		game.mdx12.SetDescriptorHeap(desc_heap_[i]);
		game.mdx12.SetGraphicsRootDescriptorTable(0, desc_heap_[i], 0);
		game.mdx12.DrawInstanced(5, 1, 0, 0);
	}
}

void DrawBoss1Component::GraphicsInit()
{
	auto& game = mObj->mScene->mGame;

	//HDrawLineFrameのシェーダを再利用
	auto vertex_shader = game.mShaderManager.GetDX12ShaderObject(4);
	auto pixel_shader = game.mShaderManager.GetDX12ShaderObject(5);

	DX12RootParameter root_param;
	root_param.mDescRanges.push_back(DX12DescriptorRange(1, DX12Config::DescriptorRangeType::CBV, 0, 0));
	root_param.mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;
	root_signature_ = game.mdx12.CreateRootSignature(root_param, false);

	DX12VertexLayout vertex_layout;
	vertex_layout.push_back(DX12VertexLayoutUnit("POSITION", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0));

	graphics_pipeline_ = game.mdx12.CreateGraphicsPipeline(
		vertex_shader, pixel_shader, vertex_layout, DX12Config::PrimitiveTopologyType::LINE, 1, root_signature_, L"DrawBoss1Component::graphics_pipeline_"
	);

	vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(XMFLOAT3) * 5, L"DrawBoss1Component::vertex_buffer_");
	XMFLOAT3* vertex_map = static_cast<XMFLOAT3*>(game.mdx12.Map(vertex_buffer_));
	vertex_map[0] = XMFLOAT3(-square_w_ / 2, +square_w_ / 2, 0.0f);
	vertex_map[1] = XMFLOAT3(-square_w_ / 2, -square_w_ / 2, 0.0f);
	vertex_map[2] = XMFLOAT3(+square_w_ / 2, -square_w_ / 2, 0.0f);
	vertex_map[3] = XMFLOAT3(+square_w_ / 2, +square_w_ / 2, 0.0f);
	vertex_map[4] = XMFLOAT3(-square_w_ / 2, +square_w_ / 2, 0.0f);
	game.mdx12.Unmap(vertex_buffer_);
	for (int i = 0; i < 4; i++)
	{
		const_buffer_[i] = game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD,sizeof(InfoToShader), L"DrawBoss1Component::const_buffer_");
		const_map_[i] = game.mdx12.Map(const_buffer_[i]);
		InfoToShader* map = static_cast<InfoToShader*>(const_map_[i]);
		map->color_ = XMFLOAT3(0.0, 0.0, 0.0);
		map->alpha_ = 1.0;
		desc_heap_[i] = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 1, L"DrawBoss1Component::desc_heap_");
		game.mdx12.CreateConstBufferView(const_buffer_[i], desc_heap_[i], 0);
	}
}

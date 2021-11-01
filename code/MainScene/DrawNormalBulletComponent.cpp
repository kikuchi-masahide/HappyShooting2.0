#include "DrawNormalBulletComponent.h"

#include "MainScene.h"

//実装のみに使う構造体
namespace{
	struct Vertex {
	public:
		XMFLOAT3 pos_;
		XMFLOAT2 uv_;
	};
	//シェーダに渡す情報
	struct InfoToShader {
	public:
		XMMATRIX mat_;
		XMFLOAT3 rgb_;
		float alpha_;
	};
}

DrawNormalBulletComponent::DrawNormalBulletComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, double radius, MatVec::Vector3 edge_rgb, double edge_alpha,double z)
	: MainSceneDrawComponent(object, layer_manager, z), radius_(radius), edge_rgb_(edge_rgb),edge_alpha_(edge_alpha)
{
	NonstaticGraphicalInit();
}

void DrawNormalBulletComponent::StaticGraphicalInit(Game& game)
{
	auto vertex_shader = game.mShaderManager.GetDX12ShaderObject(8);
	auto pixel_shader = game.mShaderManager.GetDX12ShaderObject(9);

	DX12VertexLayout vertex_layout;
	vertex_layout.push_back(DX12VertexLayoutUnit(
		"POSITION", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));
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
	root_signature_ = game.mdx12.CreateRootSignature(root_param,true);
	
	graphics_pipeline_ = game.mdx12.CreateGraphicsPipeline(
		vertex_shader,pixel_shader,vertex_layout,
		DX12Config::PrimitiveTopologyType::TRIANGLE,1,root_signature_,
		L"DrawNormalBulletComponent::graphics_pipeline_"
	);

	//0 3
	//1 2
	index_buffer_ = game.mdx12.CreateIndexBuffer(6, L"DrawNormalBulletComponent IndexBuffer");
	unsigned int* index_map = static_cast<unsigned int*>(game.mdx12.Map(index_buffer_));
	index_map[0] = 0;
	index_map[1] = 1;
	index_map[2] = 3;
	index_map[3] = 3;
	index_map[4] = 1;
	index_map[5] = 2;
	game.mdx12.Unmap(index_buffer_);

	//頂点バッファ
	vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(Vertex) * 4,L"DrawNormalBulletComponent VertexBuffer");
	Vertex vertexs[4];
	vertexs[0].uv_ = XMFLOAT2(0.0f, 0.0f);
	vertexs[1].uv_ = XMFLOAT2(0.0f, 1.0f);
	vertexs[2].uv_ = XMFLOAT2(1.0f, 1.0f);
	vertexs[3].uv_ = XMFLOAT2(1.0f, 0.0f);
	vertexs[0].pos_ = XMFLOAT3(-1.0f, +1.0f, 0.0f);
	vertexs[1].pos_ = XMFLOAT3(-1.0f, -1.0f, 0.0f);
	vertexs[2].pos_ = XMFLOAT3(+1.0f, -1.0f, 0.0f);
	vertexs[3].pos_ = XMFLOAT3(+1.0f, +1.0f, 0.0f);
	void* vertex_map = game.mdx12.Map(vertex_buffer_);
	std::memcpy(vertex_map, vertexs, sizeof(vertexs));
	game.mdx12.Unmap(vertex_buffer_);

	//定数バッファとディスクリプタヒープ群の設定
	const_buffers_.resize(max_buffers_num_);
	desc_heaps_.resize(max_buffers_num_);
	for (unsigned int n = 0; n < max_buffers_num_; n++)
	{
		std::wstring name(L"DrawNormalBulletComponent::const_buffers_[");
		name += std::to_wstring(n);
		name += L"]";
		const_buffers_[n] = game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD, sizeof(InfoToShader), name.c_str());
		name = L"DrawNormalBulletComponent::desc_heaps_[";
		name += std::to_wstring(n);
		name += L"]";
		desc_heaps_[n] = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 2, name.c_str());
		game.mdx12.CreateConstBufferView(const_buffers_[n], desc_heaps_[n], 0);
		game.mTexManager.CreateSRVof(20, desc_heaps_[n], 1);
		next_descheap_index_.push(n);
	}
}

void DrawNormalBulletComponent::NonstaticGraphicalInit()
{
	Game& game = layer_manager_->scene_->mGame;

	descheap_index_ = next_descheap_index_.front();
	next_descheap_index_.pop();
	crv_map_ = game.mdx12.Map(const_buffers_[descheap_index_]);
}

void DrawNormalBulletComponent::Draw()
{
	Game& game = layer_manager_->scene_->mGame;

	//定数バッファ
	MatVec::Matrix4x4 matrix = MatVec::Expand(radius_, radius_, 1.0);
	//円の中心
	MatVec::Vector2 center = mObj->GetPosition() + center_offset_;
	matrix = MatVec::Translation(MatVec::XY0(center)) * matrix;
	matrix = MatVec::GetOrthoGraphicProjection(600, 900, 0.0, 1.0) * matrix;
	InfoToShader info;
	info.mat_ = MatVec::ConvertToXMMATRIX(matrix);
	info.rgb_ = MatVec::ConvertToXMFLOAT3(edge_rgb_);
	info.alpha_ = edge_alpha_;
	std::memcpy(crv_map_, &info, sizeof(InfoToShader));

	//もろもろセット
	game.mdx12.SetGraphicsPipeline(graphics_pipeline_);
	game.mdx12.SetRootSignature(root_signature_);
	game.mdx12.SetDescriptorHeap(desc_heaps_[descheap_index_]);
	game.mdx12.SetGraphicsRootDescriptorTable(0, desc_heaps_[descheap_index_], 0);
	game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLELIST);
	game.mdx12.SetVertexBuffers(vertex_buffer_, 0, sizeof(Vertex) * 4, sizeof(Vertex));
	game.mdx12.SetIndexBuffers(index_buffer_,6);
	game.mdx12.SetViewports(600, 900, 0, 0, 1.0, 0.0);
	game.mdx12.SetScissorrect(0, 900, 0, 600);
	game.mdx12.DrawIndexedInstanced(6, 1, 0, 0, 0);
}

DrawNormalBulletComponent::~DrawNormalBulletComponent()
{
	next_descheap_index_.push(descheap_index_);
}

boost::shared_ptr<DX12GraphicsPipeline> DrawNormalBulletComponent::graphics_pipeline_ = nullptr;
boost::shared_ptr<DX12RootSignature> DrawNormalBulletComponent::root_signature_ = nullptr;
boost::shared_ptr<DX12Resource> DrawNormalBulletComponent::index_buffer_ = nullptr;
boost::shared_ptr<DX12Resource> DrawNormalBulletComponent::vertex_buffer_ = nullptr;
std::vector<boost::shared_ptr<DX12Resource>> DrawNormalBulletComponent::const_buffers_;
std::vector<boost::shared_ptr<DX12DescriptorHeap>> DrawNormalBulletComponent::desc_heaps_;
std::queue<unsigned int> DrawNormalBulletComponent::next_descheap_index_;
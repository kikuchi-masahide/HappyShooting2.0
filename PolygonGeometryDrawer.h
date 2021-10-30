#pragma once
#include "Game.h"
#include "code/Helper/HDrawLineFrame.h"

class PolygonGeometry;

/// <summary>
/// 1つのPolygonGeometryをCollisionUISCreenに描画するヘルパ
/// </summary>
class PolygonGeometryDrawer
{
public:
	PolygonGeometryDrawer(PolygonGeometry* polygon, MatVec::Vector3 color,Game& game);
	~PolygonGeometryDrawer();
	//vertex_buffer_の更新
	void Update();
	void Output(Game& game);
private:
	PolygonGeometry* polygon_;
	MatVec::Vector3 color_;
	static boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
	static boost::shared_ptr<DX12RootSignature> root_signature_;
	//900x900への変換とortho変換を合わせた行列を入れる
	static boost::shared_ptr<DX12Resource> matrix_buffer_;
	static void StaticGraphicInit(Game& game);
	void NonstaticGraphicInit(Game& game);
	//色情報
	boost::shared_ptr<DX12Resource> color_buffer_;
	boost::shared_ptr<DX12DescriptorHeap> desc_heap_;
	boost::shared_ptr<DX12Resource> vertex_buffer_;
	XMFLOAT3* vertex_map_;
	boost::shared_ptr<DX12Resource> index_buffer_;
	//頂点数
	int v_;
	//AABB枠描画用
	Helpers::HDrawLineFrame frame_;
};


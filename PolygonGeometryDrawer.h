#pragma once
#include "Game.h"
#include "code/Helper/HDrawLineFrame.h"

class PolygonGeometry;

/// <summary>
/// 1��PolygonGeometry��CollisionUISCreen�ɕ`�悷��w���p
/// </summary>
class PolygonGeometryDrawer
{
public:
	PolygonGeometryDrawer(PolygonGeometry* polygon, MatVec::Vector3 color,Game& game);
	~PolygonGeometryDrawer();
	//vertex_buffer_�̍X�V
	void Update();
	void Output(Game& game);
private:
	PolygonGeometry* polygon_;
	MatVec::Vector3 color_;
	static boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
	static boost::shared_ptr<DX12RootSignature> root_signature_;
	//900x900�ւ̕ϊ���ortho�ϊ������킹���s�������
	static boost::shared_ptr<DX12Resource> matrix_buffer_;
	static void StaticGraphicInit(Game& game);
	void NonstaticGraphicInit(Game& game);
	//�F���
	boost::shared_ptr<DX12Resource> color_buffer_;
	boost::shared_ptr<DX12DescriptorHeap> desc_heap_;
	boost::shared_ptr<DX12Resource> vertex_buffer_;
	XMFLOAT3* vertex_map_;
	boost::shared_ptr<DX12Resource> index_buffer_;
	//���_��
	int v_;
	//AABB�g�`��p
	Helpers::HDrawLineFrame frame_;
};


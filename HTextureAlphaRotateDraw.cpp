#include "stdafx.h"
#include "HTextureAlphaRotateDraw.h"

HTextureAlphaRotateDraw::HTextureAlphaRotateDraw(Game& game, unsigned int textureid)
{
	//�ʎZ1�ڂ̃C���X�^���X
	if (info_to_shader_ == nullptr)
	{
		StaticGraphicInit(game);
	}
	texture_id_ = textureid;
	NonstaticGraphicsInit(game);
}

void HTextureAlphaRotateDraw::Draw(Game& game, double center_x, double center_y, double width, double height, double angle, double alpha, double rt_width, double rt_height)
{
	//�V�F�[�_�[�ɓn�����
	*alpha_map_ = alpha;

	//���_���W��ω�������
	//(�V�F�[�_�ɍs���n���ƂȂ��������`���c�񂾂̂�)
	MatVec::Matrix4x4 matrix = MatVec::Rotate(MatVec::GetQuaternion(
		MatVec::Vector3(0, 0, 1), -angle
	));
	matrix = MatVec::Translation(MatVec::Vector3(center_x, center_y, 0))*matrix;
	MatVec::Vector4 points_before[4];
	points_before[0] = MatVec::Vector4(-width / 2, height / 2, 0.0, 1.0);
	points_before[1] = MatVec::Vector4(-width / 2, -height / 2, 0.0, 1.0);
	points_before[2] = MatVec::Vector4(width / 2, -height / 2, 0.0, 1.0);
	points_before[3] = MatVec::Vector4(width / 2, height / 2, 0.0, 1.0);
	float* vertex_map = static_cast<float*>(game.mdx12.Map(vertex_buffer_));
	for (unsigned int n = 0; n < 4; n++)
	{
		points_before[n] = matrix * points_before[n];
		points_before[n][0] /= points_before[n][3];
		points_before[n][1] /= points_before[n][3];
		points_before[n][2] /= points_before[n][3];
		points_before[n][0] = 2 * points_before[n][0] / rt_width - 1;
		points_before[n][1] = 2 * points_before[n][1] / rt_height - 1;
		vertex_map[5 * n + 0] = points_before[n][0];
		vertex_map[5 * n + 1] = points_before[n][1];
		vertex_map[5 * n + 2] = points_before[n][2];
	}
	game.mdx12.Unmap(vertex_buffer_);

	//�p�C�v���C�����s
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
	//���[�g�p�����^0:
	//	�����W0:SRV,t0~t0 <---> �e�N�X�`���̃q�[�v
	//
	//���[�g�p�����^1:
	//	�����W0:CRV,b0~b0 <---> info_crv_heap_
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

	//�C���f�b�N�X�o�b�t�@
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

	//���_�o�b�t�@
	vertex_buffer_ = game.mdx12.CreateVertexBuffer(sizeof(Vertex) * 4);
	Vertex* vertexmap = static_cast<Vertex*>(game.mdx12.Map(vertex_buffer_));
	vertexmap[0] = Vertex(-0.5, 0.5, 0.0, 0.0, 0.0);
	vertexmap[1] = Vertex(-0.5, -0.5, 0.0, 0.0, 1.0);
	vertexmap[2] = Vertex(0.5, -0.5, 0.0, 1.0, 1.0);
	vertexmap[3] = Vertex(0.5, 0.5, 0.0, 1.0, 0.0);
	game.mdx12.Unmap(vertex_buffer_);

	//�V�F�[�_�[�擾
	auto vertexshader = game.mShaderManager.GetDX12ShaderObject(6);
	auto pixelshader = game.mShaderManager.GetDX12ShaderObject(7);

	//���_���C�A�E�g
	DX12VertexLayout vertexlayout;
	vertexlayout.push_back(DX12VertexLayoutUnit(
		"POSITION", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));
	vertexlayout.push_back(DX12VertexLayoutUnit(
		"TEXCOORD", DX12Config::VertexLayoutFormat::R32G32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));

	//�p�C�v���C���쐬
	graphics_pipeline_ = game.mdx12.CreateGraphicsPipeline(
		vertexshader, pixelshader, vertexlayout, DX12Config::PrimitiveTopologyType::TRIANGLE, 1, rootsignature_
	);
}

void HTextureAlphaRotateDraw::NonstaticGraphicsInit(Game& game)
{
	//�萔�o�b�t�@������
	info_to_shader_ = game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD, sizeof(float));
	info_crv_heap_ = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 1);
	game.mdx12.CreateConstBufferView(info_to_shader_, info_crv_heap_, 0);
	alpha_map_ = static_cast<float*>(game.mdx12.Map(info_to_shader_));

	//�e�N�X�`��srv�ǂݍ���
	auto res = game.mTexManager.GetDX12DescriptorHeap(texture_id_);
	srv_heap_ = res.first;
	srv_heap_ind_ = res.second;
}

boost::shared_ptr<DX12GraphicsPipeline> HTextureAlphaRotateDraw::graphics_pipeline_ = nullptr;
boost::shared_ptr<DX12RootSignature> HTextureAlphaRotateDraw::rootsignature_ = nullptr;
boost::shared_ptr<DX12Resource> HTextureAlphaRotateDraw::vertex_buffer_ = nullptr;
boost::shared_ptr<DX12Resource> HTextureAlphaRotateDraw::index_buffer_ = nullptr;
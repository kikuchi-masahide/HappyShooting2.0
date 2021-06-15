#include "HTextureDraw.h"

void HTextureDraw::DrawInRect(Game& _game, double _lx, double _rx, double _by, double _ty, unsigned int _rtwidth, unsigned int _rtheight)
{
	//�ό`�s����Z�b�g����
	//���W��-1~1�ɕϊ�
	_lx = 2 * _lx / _rtwidth - 1;
	_rx = 2 * _rx / _rtwidth - 1;
	_ty = 2 * _ty / _rtheight - 1;
	_by = 2 * _by / _rtheight - 1;
	//�g��
	MatVec::Matrix4d mat = MatVec::Expand(_rx - _lx, _ty - _by, 1);
	//���s�ړ�
	mat = MatVec::Translation((_lx + _rx) / 2, (_by + _ty) / 2, 0) * mat;
	//�萔�o�b�t�@�Ƀ}�b�v
	_game.mdx12.Copy4x4Matrix(matrix_map, mat);
	//�p�C�v���C��
	_game.mdx12.SetGraphicsPipeline(mGPipeline);
	//���[�g�V�O�l�`��
	_game.mdx12.SetRootSignature(mRootSignature);
	//�f�B�X�N���v�^�q�[�v�̃Z�b�g
	//���[�g�V�O�l�`���̍\����GraphicalInit�Q��
	_game.mdx12.SetDescriptorHeap(mSRVHeap);
	_game.mdx12.SetGraphicsRootDescriptorTable(0, mSRVHeap, mSRVHeapIndex);
	_game.mdx12.SetDescriptorHeap(mCRVDescHeap);
	_game.mdx12.SetGraphicsRootDescriptorTable(1, mCRVDescHeap, 0);
	//�v���~�e�B�u�g�|���W
	_game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLESTRIP);
	//���_�o�b�t�@�w��
	_game.mdx12.SetVertexBuffers(mVertexBuffer, 0, sizeof(Vertex) * 4, sizeof(Vertex));
	//�C���f�b�N�X�o�b�t�@
	_game.mdx12.SetIndexBuffers(mIndexBuffer, 6);
	//�r���[�|�[�g
	_game.mdx12.SetViewports(900, 900, 0, 0, 1.0f, 0.0f);
	_game.mdx12.SetScissorrect(0, 900, 0, 900);
	//�`��
	_game.mdx12.DrawIndexedInstanced(6, 1, 0, 0, 0);
}

void HTextureDraw::DrawCenter(Game& _game, double _cx, double _cy, double _rx, double _ry, unsigned int _rtwidth, unsigned int _rtheight)
{
	double lx = _cx - _rx / 2;
	double rx = _cx + _rx / 2;
	double by = _cy - _ry / 2;
	double ty = _cy + _ry / 2;
	DrawInRect(_game, lx, rx, by, ty, _rtwidth, _rtheight);
}

HTextureDraw::HTextureDraw(Game& _game, unsigned int _textureid)
{
	//�����ݒ肪�I����Ă��Ȃ��ꍇ�̂݌Ăяo��
	if (mGPipeline == nullptr)
	{
		GraphicInit(_game);
	}
	ReadSRV(_game,_textureid);
}

void HTextureDraw::GraphicInit(Game& _game)
{
	//���[�g�p�����^0:
	//	�����W0:SRV,t0~t0 <---> �e�N�X�`���̃q�[�v
	//
	//���[�g�p�����^1:
	//	�����W0:CRV,b0~b0 <---> mCRVDescHeap

	//SRV�q�[�v�p���[�g�p�����[�^
	DX12RootParameter srv_root_param;
	srv_root_param.mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;
	//SRV��1�}��(�V�F�[�_���W�X�^0�Ԃ���)
	srv_root_param.mDescRanges.push_back(DX12DescriptorRange(
		1, DX12Config::DescriptorRangeType::SRV, 0, 0
	));

	//mCRVDescHeap�p���[�g�p�����[�^
	DX12RootParameter crv_root_param;
	crv_root_param.mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;
	//crv��1�}��
	crv_root_param.mDescRanges.push_back(DX12DescriptorRange(
		1, DX12Config::DescriptorRangeType::CBV, 0, 0
	));

	std::vector<DX12RootParameter> root_params(2);
	root_params[0] = srv_root_param;
	root_params[1] = crv_root_param;
	//���[�g�V�O�l�`��
	mRootSignature = _game.mdx12.CreateRootSignature(root_params);

	//�C���f�b�N�X�o�b�t�@
	mIndexBuffer = _game.mdx12.CreateIndexBuffer(6);
	unsigned int* indexmap = (unsigned int*)_game.mdx12.Map(mIndexBuffer);
	//0 3
	//1 2
	indexmap[0] = 0;
	indexmap[1] = 1;
	indexmap[2] = 3;
	indexmap[3] = 1;
	indexmap[4] = 2;
	indexmap[5] = 3;
	_game.mdx12.Unmap(mIndexBuffer);
	//���_�o�b�t�@
	mVertexBuffer = _game.mdx12.CreateVertexBuffer(sizeof(Vertex) * 4);
	Vertex* vertexmap = (Vertex*)_game.mdx12.Map(mVertexBuffer);
	vertexmap[0] = Vertex(-0.5, 0.5, 0.0, 0.0, 0.0);
	vertexmap[1] = Vertex(-0.5, -0.5, 0.0, 0.0, 1.0);
	vertexmap[2] = Vertex(0.5, -0.5, 0.0, 1.0, 1.0);
	vertexmap[3] = Vertex(0.5, 0.5, 0.0, 1.0, 0.0);
	_game.mdx12.Unmap(mVertexBuffer);
	//�V�F�[�_�[�擾
	auto vertexshader = _game.mShaderManager.GetDX12ShaderObject(0);
	auto pixelshader = _game.mShaderManager.GetDX12ShaderObject(1);
	//���_���C�A�E�g
	DX12VertexLayout vertexlayout;
	vertexlayout.push_back(DX12VertexLayoutUnit(
		"POSITION", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT,0,DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
	));
	vertexlayout.push_back(DX12VertexLayoutUnit(
		"TEXCOORD", DX12Config::VertexLayoutFormat::R32G32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));
	//�p�C�v���C���쐬
	mGPipeline = _game.mdx12.CreateGraphicsPipeline(
		vertexshader, pixelshader, vertexlayout, DX12Config::PrimitiveTopologyType::TRIANGLE, 1, mRootSignature
	);
	//�萔�o�b�t�@�쐬
	mMatrixBuffer = _game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD,sizeof(double)*16);
	//�萔�o�b�t�@�̃q�[�v
	mCRVDescHeap = _game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 1);
	//�萔�o�b�t�@�̃r���[
	_game.mdx12.CreateConstBufferView(mMatrixBuffer, mCRVDescHeap, 0);
	//�s��}�b�v���ݒ�
	matrix_map = _game.mdx12.Map(mMatrixBuffer);
}

void HTextureDraw::ReadSRV(Game& _game, unsigned int _textureid)
{
	auto res = _game.mTexManager.GetDX12DescriptorHeap(_textureid);
	mSRVHeap = res.first;
	mSRVHeapIndex = res.second;
}

boost::shared_ptr<DX12GraphicsPipeline> HTextureDraw::mGPipeline = nullptr;
boost::shared_ptr<DX12RootSignature> HTextureDraw::mRootSignature = nullptr;
boost::shared_ptr<DX12Resource> HTextureDraw::mIndexBuffer = nullptr;
boost::shared_ptr<DX12Resource> HTextureDraw::mVertexBuffer = nullptr;
boost::shared_ptr<DX12Resource> HTextureDraw::mMatrixBuffer = nullptr;
boost::shared_ptr<DX12DescriptorHeap> HTextureDraw::mCRVDescHeap = nullptr;
void* HTextureDraw::matrix_map = nullptr;
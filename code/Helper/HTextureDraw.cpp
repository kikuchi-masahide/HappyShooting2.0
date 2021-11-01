#include "HTextureDraw.h"

namespace Helpers {

	namespace {
		struct InfoToShader {
		public:
			XMMATRIX matrix;
		};
	}

	void HTextureDraw::DrawInRect(Game& _game, double _lx, double _rx, double _by, double _ty, unsigned int _rtwidth, unsigned int _rtheight)
	{
		//�ό`�s����Z�b�g����
		//�g��
		MatVec::Matrix4x4 mat = MatVec::Expand(_rx - _lx, _ty - _by, 1);
		//���s�ړ�
		mat = MatVec::Translation((_lx + _rx) / 2, (_by + _ty) / 2, 0) * mat;
		mat = MatVec::GetOrthoGraphicProjection(_rtwidth, _rtheight, 0.0, 1.0) * mat;
		//�萔�o�b�t�@�Ƀ}�b�v
		InfoToShader* matmap = static_cast<InfoToShader*>(matrix_map);
		matmap->matrix = MatVec::ConvertToXMMATRIX(mat);
		//�p�C�v���C��
		_game.mdx12.SetGraphicsPipeline(mGPipeline);
		//���[�g�V�O�l�`��
		_game.mdx12.SetRootSignature(mRootSignature);
		//�f�B�X�N���v�^�q�[�v�̃Z�b�g
		//���[�g�V�O�l�`���̍\����GraphicalInit�Q��
		_game.mdx12.SetDescriptorHeap(mDescHeap);
		_game.mdx12.SetGraphicsRootDescriptorTable(0, mDescHeap, 0);
		//�v���~�e�B�u�g�|���W
		_game.mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLELIST);
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
			StaticGraphicInit(_game);
		}
		InitializeConstBuffer(_game);
		InitializeDescHeap(_game, _textureid);
	}

	void HTextureDraw::StaticGraphicInit(Game& _game)
	{
		//���[�g�p�����^0:
		//	�����W0:SRV,t0~t0 <---> �e�N�X�`���̃q�[�v
		//	�����W0:CRV,b0~b0 <---> mCRVDescHeap

		//SRV�q�[�v�p���[�g�p�����[�^
		DX12RootParameter root_param;
		root_param.mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;
		//SRV��1�}��(�V�F�[�_���W�X�^0�Ԃ���)
		root_param.mDescRanges.push_back(DX12DescriptorRange(
			1, DX12Config::DescriptorRangeType::SRV, 0, 0
		));
		root_param.mDescRanges.push_back(DX12DescriptorRange(
			1, DX12Config::DescriptorRangeType::CBV, 0, 1
		));
		//���[�g�V�O�l�`��
		mRootSignature = _game.mdx12.CreateRootSignature(root_param);

		//�C���f�b�N�X�o�b�t�@
		mIndexBuffer = _game.mdx12.CreateIndexBuffer(6, L"HTextureDraw IndexBuffer");
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
		mVertexBuffer = _game.mdx12.CreateVertexBuffer(sizeof(Vertex) * 4, L"HTextureDraw VertexBuffer");
		void* vertexmap = _game.mdx12.Map(mVertexBuffer);
		Vertex vertexs_[4];
		vertexs_[0].uv_ = XMFLOAT2(0.0f, 0.0f);
		vertexs_[1].uv_ = XMFLOAT2(0.0f, 1.0f);
		vertexs_[2].uv_ = XMFLOAT2(1.0f, 1.0f);
		vertexs_[3].uv_ = XMFLOAT2(1.0f, 0.0f);
		vertexs_[0].pos_ = XMFLOAT3(-0.5f, +0.5f, 0.0f);
		vertexs_[1].pos_ = XMFLOAT3(-0.5f, -0.5f, 0.0f);
		vertexs_[2].pos_ = XMFLOAT3(+0.5f, -0.5f, 0.0f);
		vertexs_[3].pos_ = XMFLOAT3(+0.5f, +0.5f, 0.0f);
		std::memcpy(vertexmap, vertexs_, sizeof(vertexs_));
		_game.mdx12.Unmap(mVertexBuffer);
		//�V�F�[�_�[�擾
		auto vertexshader = _game.mShaderManager.GetDX12ShaderObject(0);
		auto pixelshader = _game.mShaderManager.GetDX12ShaderObject(1);
		//���_���C�A�E�g
		DX12VertexLayout vertexlayout;
		vertexlayout.push_back(DX12VertexLayoutUnit(
			"POSITION", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		));
		vertexlayout.push_back(DX12VertexLayoutUnit(
			"TEXCOORD", DX12Config::VertexLayoutFormat::R32G32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		));
		//�p�C�v���C���쐬
		mGPipeline = _game.mdx12.CreateGraphicsPipeline(
			vertexshader, pixelshader, vertexlayout, DX12Config::PrimitiveTopologyType::TRIANGLE, 1, mRootSignature, L"HTextureDraw::mGPipeline"
		);
	}

	void HTextureDraw::InitializeDescHeap(Game& _game, unsigned int _textureid)
	{
		mDescHeap = _game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 2, L"HTextureDraw::,DescHeap");
		_game.mTexManager.CreateSRVof(_textureid, mDescHeap, 0);
		_game.mdx12.CreateConstBufferView(mMatrixBuffer, mDescHeap, 1);
	}

	void HTextureDraw::InitializeConstBuffer(Game& game)
	{
		//�萔�o�b�t�@�쐬
		mMatrixBuffer = game.mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD, sizeof(InfoToShader), L"HTextureDraw ConstBuffer");
		//�s��}�b�v���ݒ�
		matrix_map = game.mdx12.Map(mMatrixBuffer);
	}

	boost::shared_ptr<DX12GraphicsPipeline> HTextureDraw::mGPipeline = nullptr;
	boost::shared_ptr<DX12RootSignature> HTextureDraw::mRootSignature = nullptr;
	boost::shared_ptr<DX12Resource> HTextureDraw::mIndexBuffer = nullptr;
	boost::shared_ptr<DX12Resource> HTextureDraw::mVertexBuffer = nullptr;

}
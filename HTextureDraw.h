#pragma once
#include "Game.h"

//�e�N�X�`���̕`����w����W�ɍs���w���p
//RTV���J������ԂłȂ��Ƃ����Ȃ�
class HTextureDraw
{
public:
	/// <param name="_textureid">���̃C���X�^���X�ŕ`���e�N�X�`����ID</param>
	HTextureDraw(Game& _game,unsigned int _textureid);
	/// <summary>
	/// RTV���J������ԂŁC�w����W�Ƀe�N�X�`����`��
	/// </summary>
	/// <param name="_lx">���[x[px]</param>
	/// <param name="_rx">�E�[x[px]</param>
	/// <param name="_by">���[y[px]</param>
	/// <param name="_ty">��[y[px]</param>
	/// <param name="_rtwidth">�����_�[�^�[�Q�b�g�̉���[px]</param>
	/// <param name="_rtheight">�����_�[�^�[�Q�b�g�̏c��[px]</param>
	void DrawInRect(Game& _game, double _lx, double _rx, double _by, double _ty, unsigned int _rtwidth,unsigned int _rtheight);
	/// <summary>
	/// RTV���J������ԂŁC���S�_�Ɣ{�����w�肵�ăe�N�X�`����`��
	/// </summary>
	/// <param name="_cx">���Sx[px]</param>
	/// <param name="_cy">���Sy[px]</param>
	/// <param name="_rx">��[px]</param>
	/// <param name="_ry">����[px]</param>
	/// <param name="_rtwidth">�����_�[�^�[�Q�b�g�̉���[px]</param>
	/// <param name="_rtheight">�����_�[�^�[�Q�b�g�̏c��[px]</param>
	void DrawCenter(Game& _game, double _cx, double _cy, double _rx, double _ry, unsigned int _rtwidth, unsigned int _rtheight);
private:
	static boost::shared_ptr<DX12GraphicsPipeline> mGPipeline;
	static boost::shared_ptr<DX12RootSignature> mRootSignature;
	static boost::shared_ptr<DX12Resource> mIndexBuffer;
	static boost::shared_ptr<DX12Resource> mVertexBuffer;
	//�g��E���s�ړ��p�̒萔�o�b�t�@�Ƃ��̃r���[�̂��߂̃q�[�v
	boost::shared_ptr<DX12Resource> mMatrixBuffer;
	boost::shared_ptr<DX12DescriptorHeap> mCRVDescHeap;
	//�p�C�v���C�����̏�����
	static void GraphicInit(Game& _game);
	//�R���X�g���N�^�ŌĂяo����SRV�̓ǂݍ��݂��s��
	void ReadSRV(Game& _game,unsigned int _textureid);
	//�R���X�g���N�^�ŌĂяo����C�萔�o�b�t�@�Ƃ���CRV�̏��������s��
	void InitializeCRV(Game& game);
	struct Vertex {
	public:
		float x, y, z;
		float u, v;
		Vertex(float _x, float _y, float _z, float _u, float _v)
			:x(_x),y(_y),z(_z),u(_u),v(_v){}
	};
	//SRV�̓����Ă���q�[�v�Ƃ��̔ԍ�
	boost::shared_ptr<DX12DescriptorHeap> mSRVHeap;
	unsigned int mSRVHeapIndex;
	//�e�N�X�`���̑傫��
	double texWidth_;
	double texHeight_;
	//�s��}�b�v��
	void* matrix_map;
};
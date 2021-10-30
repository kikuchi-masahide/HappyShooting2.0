#pragma once
#include "../Game.h"

namespace Helpers {

	//�e�N�X�`���̕`����w����W�ɍs���w���p
	//RTV���J������ԂłȂ��Ƃ����Ȃ�
	class HTextureDraw
	{
	public:
		/// <param name="_textureid">���̃C���X�^���X�ŕ`���e�N�X�`����ID</param>
		HTextureDraw(Game& _game, unsigned int _textureid);
		/// <summary>
		/// RTV���J������ԂŁC�w����W�Ƀe�N�X�`����`��
		/// </summary>
		/// <param name="_lx">���[x(�����_�[�^�[�Q�b�g���S�����_)[px]</param>
		/// <param name="_rx">�E�[x(�����_�[�^�[�Q�b�g���S�����_)[px]</param>
		/// <param name="_by">���[y(�����_�[�^�[�Q�b�g���S�����_)[px]</param>
		/// <param name="_ty">��[y(�����_�[�^�[�Q�b�g���S�����_)[px]</param>
		/// <param name="_rtwidth">�����_�[�^�[�Q�b�g�̉���[px]</param>
		/// <param name="_rtheight">�����_�[�^�[�Q�b�g�̏c��[px]</param>
		void DrawInRect(Game& _game, double _lx, double _rx, double _by, double _ty, unsigned int _rtwidth, unsigned int _rtheight);
		/// <summary>
		/// RTV���J������ԂŁC���S�_�Ɣ{�����w�肵�ăe�N�X�`����`��
		/// </summary>
		/// <param name="_cx">���Sx(�����_�[�^�[�Q�b�g���S�����_)[px]</param>
		/// <param name="_cy">���Sy(�����_�[�^�[�Q�b�g���S�����_)[px]</param>
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
		boost::shared_ptr<DX12DescriptorHeap> mDescHeap;
		//�p�C�v���C�����̏�����
		static void StaticGraphicInit(Game& _game);
		void InitializeDescHeap(Game& _game, unsigned int _textureid);
		//�R���X�g���N�^�ŌĂяo����C�萔�o�b�t�@�Ƃ���CRV�̏��������s��
		void InitializeConstBuffer(Game& game);
		struct Vertex {
		public:
			XMFLOAT3 pos_;
			XMFLOAT2 uv_;
		};
		//�e�N�X�`���̑傫��
		double texWidth_;
		double texHeight_;
		//�s��}�b�v��
		void* matrix_map;
	};

}
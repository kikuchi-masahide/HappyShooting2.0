#pragma once
#include "../Engine/Game.h"

namespace Helpers {

	/// <summary>
	/// �e�N�X�`�������Ɗp�x���w�肵�ĕ`�悷��
	/// </summary>
	class HTextureAlphaRotateDraw
	{
	public:
		HTextureAlphaRotateDraw(Game& game, unsigned int textureid);
		/// <summary>
		/// RTV���J������ԂŁC�w����W�Ɏw��p�x������]���Ďw�胿�Ńe�N�X�`����`��
		/// </summary>
		/// <param name="center_x">RTV���S�����_�Ƃ����Ƃ��́C�e�N�X�`�����S���Wx[px]</param>
		/// <param name="center_y">RTV���S�����_�Ƃ����Ƃ��́C�e�N�X�`�����S���Wy[px]</param>
		/// <param name="width">�e�N�X�`��������px�ɂ��邩</param>
		/// <param name="height">�e�N�X�`����������px�ɂ��邩</param>
		/// <param name="angle">�����v���ŉ�]�p�x[rad]</param>
		/// <param name="alpha">�s�����x</param>
		/// <param name="rt_width">�����_�[�^�[�Q�b�g��</param>
		/// <param name="rt_height">�����_�[�^�[�Q�b�g����</param>
		void Draw(Game& game, double center_x, double center_y, double width, double height, double angle, double alpha, double rt_width, double rt_height);
	private:
		static boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
		static boost::shared_ptr<DX12RootSignature> rootsignature_;
		static boost::shared_ptr<DX12Resource> vertex_buffer_;
		static boost::shared_ptr<DX12Resource> index_buffer_;
		//�V�F�[�_�[�ɓn�����̃��\�[�X
		boost::shared_ptr<DX12Resource> info_to_shader_;
		boost::shared_ptr<DX12DescriptorHeap> desc_heap_;
		//�r���[���q�[�v�̂ǂ��ɓ����Ă��邩
		unsigned int srv_heap_ind_;
		//�e�N�X�`��ID
		unsigned int texture_id_;
		//�e�N�X�`���̑傫��
		double tex_width_;
		double tex_height_;
		//�V�F�[�_�ɓn�����̃}�b�v��
		void* info_to_shader_map_;
		//static�ȃO���t�B�b�N�֘A�ϐ��̏�����
		void static StaticGraphicInit(Game& game);
		//��static�ȃO���t�B�b�N�֘A�ϐ��̏�����
		void NonstaticGraphicsInit(Game& game);
	};

}
#pragma once
#include "Game.h"

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
	/// <param name="center_x">���S���Wx[px]</param>
	/// <param name="center_y">���S���Wy[px]</param>
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
	//info_to_shader_�̃r���[����q�[�v
	boost::shared_ptr<DX12DescriptorHeap> info_crv_heap_;
	//�e�N�X�`����srv
	boost::shared_ptr<DX12DescriptorHeap> srv_heap_;
	//�r���[���q�[�v�̂ǂ��ɓ����Ă��邩
	unsigned int srv_heap_ind_;
	//�e�N�X�`��ID
	unsigned int texture_id_;
	//�e�N�X�`���̑傫��
	double tex_width_;
	double tex_height_;
	//�s�����x�}�b�v��
	float* alpha_map_;
	//���_�o�b�t�@��1���_���
	struct Vertex {
	public:
		float x, y, z;
		float u, v;
		Vertex(double _x, double _y, double _z, double _u, double _v)
			:x(_x), y(_y), z(_z), u(_u), v(_v) {}
	};
	//static�ȃO���t�B�b�N�֘A�ϐ��̏�����
	void static StaticGraphicInit(Game& game);
	//��static�ȃO���t�B�b�N�֘A�ϐ��̏�����
	void NonstaticGraphicsInit(Game& game);
};


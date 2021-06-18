#pragma once
#include "Game.h"

//�����_�[�^�[�Q�b�g���Z�b�g���ꂽ��ԂŁC�w����W�Ɏw��p�x�Řg����`��
class HDrawLineFrame
{
public:
	HDrawLineFrame(Game& game);
	/// <summary>
	/// �����_�[�^�[�Q�b�g���Z�b�g���ꂽ��ԂŁC���S�Ɖ�]�p�x���w�肵�Ęg����`�悷��
	/// </summary>
	/// <param name="rt_width">�����_�[�^�[�Q�b�g��</param>
	/// <param name="rt_height">�����_�[�^�[�Q�b�g����</param>
	void DrawFrame(Game& game, double center_x, double center_y, double width,double height,double angle, unsigned int rt_width, unsigned int rt_height);
private:
	static boost::shared_ptr<DX12GraphicsPipeline> pipeline_;
	static boost::shared_ptr<DX12Resource> vertex_buffer_;
	static boost::shared_ptr<DX12RootSignature> root_signature_;
	static void GraphicInit(Game& game);
};


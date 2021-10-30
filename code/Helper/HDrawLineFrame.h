#pragma once
#include "../Engine/Game.h"

namespace Helpers {

	//�����_�[�^�[�Q�b�g���Z�b�g���ꂽ��ԂŁC�w����W�Ɏw��p�x�Řg����`��
	class HDrawLineFrame
	{
	public:
		HDrawLineFrame(Game& game);
		/// <summary>
		/// �����_�[�^�[�Q�b�g���Z�b�g���ꂽ��ԂŁC���S�Ɖ�]�p�x���w�肵�Ęg����`�悷��
		/// </summary>
		/// <param name="center_x">�����_�[�^�[�Q�b�g���S�����_�̂Ƃ��́C�t���[�����Sx[px]</param>
		/// <param name="center_y">�����_�[�^�[�Q�b�g���S�����_�̂Ƃ��́C�t���[�����Sy[px]</param>
		/// <param name="rt_width">�����_�[�^�[�Q�b�g��</param>
		/// <param name="rt_height">�����_�[�^�[�Q�b�g����</param>
		/// <param name="color">�g���̐F(�ȗ����s�������F)</param>
		void DrawFrame(Game& game, double center_x, double center_y, double width, double height, double angle, unsigned int rt_width, unsigned int rt_height,MatVec::Vector4 color = MatVec::Vector4(0.0,0.0,0.0,1.0));
	private:
		static boost::shared_ptr<DX12GraphicsPipeline> pipeline_;
		static boost::shared_ptr<DX12Resource> vertex_buffer_;
		static boost::shared_ptr<DX12RootSignature> root_signature_;
		static void StaticGraphicInit(Game& game);
		boost::shared_ptr<DX12Resource> const_buffer_;
		boost::shared_ptr<DX12DescriptorHeap> crv_heap_;
		void* map_;
	};

}
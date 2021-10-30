#pragma once
#include "../Engine/Game.h"

class UIScreen;

namespace Helpers {
	class HUIButton
	{
	public:
		/// <param name="texture_away">�}�E�X���{�^����ɂȂ��Ƃ��̃e�N�X�`��</param>
		/// <param name="texture_over">�}�E�X���{�^����ɂ���Ƃ��̃e�N�X�`��</param>
		/// <param name="centerx">�{�^���̒��Sx���W</param>
		/// <param name="width">�{�^����x���W��</param>
		/// <param name="centery">�{�^���̒��Sy���W</param>
		/// <param name="height">�{�^����y���W����</param>
		/// <param name="action">�{�^���������ꂽ�Ƃ��̃A�N�V����</param>
		HUIButton(UIScreen* screen, unsigned int texture_away, unsigned int texture_over, double centerx, double width, double centery, double height, std::function<void(HUIButton* button)> action);
		~HUIButton();
		void Update();
		void Output();
		UIScreen* const screen_;
	private:
		static boost::shared_ptr<DX12GraphicsPipeline> pipeline_;
		static boost::shared_ptr<DX12RootSignature> root_signature_;
		//�}�E�X����ɖ������Ƃ��鎞�Ńq�[�v���g��������
		boost::shared_ptr<DX12DescriptorHeap> descheap_away_;
		boost::shared_ptr<DX12DescriptorHeap> descheap_over_;
		static boost::shared_ptr<DX12Resource> vertex_buffer_;
		static boost::shared_ptr<DX12Resource> index_buffer_;
		boost::shared_ptr<DX12Resource> const_buffer_;
		static void StaticGraphicInit(Game& game);
		void NonstaticGraphicInit(Game& game, unsigned int texture_away, unsigned int texture_over);
		double centerx_;
		double centery_;
		double width_;
		double height_;
		//�N���b�N��(�{�^����ō��{�^���������ꂽ)�̓���
		std::function<void(HUIButton* button)> click_action_;
		//Update�ōX�V
		bool is_mouse_over_;
	};
}

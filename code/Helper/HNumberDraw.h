#pragma once
#include "../Engine/Game.h"

namespace Helpers {

	//�n���ꂽ������`�悷�邽�߂̃w���p
	class HNumberDraw final
	{
	public:
		HNumberDraw(Game& game, double font_size, MatVec::Vector2 leftup_position, unsigned int rt_width, unsigned int rt_height, unsigned int max_digit);
		~HNumberDraw();
		//�t�H���g�T�C�Y(px)
		double font_size_;
		//�\���ӏ�����̍��W(RT���S���_px�P��)
		MatVec::Vector2 leftup_position_;
		unsigned int rt_width_;
		unsigned int rt_height_;
		//�\���\�ő包��(��8)
		unsigned int max_digit_;
		void DrawNumber(Game& game, int number);
	private:
		static boost::shared_ptr<DX12GraphicsPipeline> pipeline_;
		static boost::shared_ptr<DX12RootSignature> root_signature_;
		//�����ɂ��C���f�b�N�X�o�b�t�@�̒������ς��
		boost::shared_ptr<DX12Resource> index_buffer_;
		boost::shared_ptr<DX12Resource> vertex_buffer_;
		//SRV,CRV
		boost::shared_ptr<DX12DescriptorHeap> desc_heap_;
		//�ϊ��s��C�����牽�Ԗڂ̘g�����̐�����\�����邩 �𑗂�萔�o�b�t�@
		boost::shared_ptr<DX12Resource> const_buffer_;
		void* const_map_;
		static void StaticGraphicInit(Game& game);
		void NonstaticGraphicInit(Game& game);
	};

}
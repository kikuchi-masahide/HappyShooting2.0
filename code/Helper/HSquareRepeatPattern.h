#pragma once
#include "../Engine/Game.h"

namespace Helpers {

	//�摜�𒷕��`�̈�ɕ~���l��
	class HSquareRepeatPattern
	{
	public:
		/// <param name="texture_width">�e�N�X�`���̕�(�Œ�)</param>
		/// <param name="texture_height">�e�N�X�`���̍���(�Œ�)</param>
		HSquareRepeatPattern(Game& game, unsigned int texture_id, double texture_width, double texture_height);
		~HSquareRepeatPattern();
		/// <summary>
		/// RT���J���ꂽ��ԂŁC���̓_�𒆐S�Ƃ��āC�w��摜���~���l�߂��Ă��钷���`��`�悷��
		/// </summary>
		void Draw(Game& game, MatVec::Vector2 center, double square_width, double square_height, double alpha, double rt_width, double rt_height);
	private:
		const unsigned int texture_id_;
		const double texture_width_;
		const double texture_height_;
		static boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
		static boost::shared_ptr<DX12RootSignature> root_signature_;
		static boost::shared_ptr<DX12Resource> index_buffer_;
		static void StaticGraphicInit(Game& game);
		boost::shared_ptr<DX12Resource> vertex_buffer_;
		boost::shared_ptr<DX12Resource> const_buffer_;
		boost::shared_ptr<DX12DescriptorHeap> desc_heap_;
		void* vertex_map_;
		void* cbuffer_map_;
		void NonstaticGraphicInit(Game& game);
	};

}
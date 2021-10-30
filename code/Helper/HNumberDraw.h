#pragma once
#include "../Engine/Game.h"

namespace Helpers {

	//渡された整数を描画するためのヘルパ
	class HNumberDraw final
	{
	public:
		HNumberDraw(Game& game, double font_size, MatVec::Vector2 leftup_position, unsigned int rt_width, unsigned int rt_height, unsigned int max_digit);
		~HNumberDraw();
		//フォントサイズ(px)
		double font_size_;
		//表示箇所左上の座標(RT中心原点px単位)
		MatVec::Vector2 leftup_position_;
		unsigned int rt_width_;
		unsigned int rt_height_;
		//表示可能最大桁数(≦8)
		unsigned int max_digit_;
		void DrawNumber(Game& game, int number);
	private:
		static boost::shared_ptr<DX12GraphicsPipeline> pipeline_;
		static boost::shared_ptr<DX12RootSignature> root_signature_;
		//桁数によりインデックスバッファの長さが変わる
		boost::shared_ptr<DX12Resource> index_buffer_;
		boost::shared_ptr<DX12Resource> vertex_buffer_;
		//SRV,CRV
		boost::shared_ptr<DX12DescriptorHeap> desc_heap_;
		//変換行列，左から何番目の枠が何の数字を表示するか を送る定数バッファ
		boost::shared_ptr<DX12Resource> const_buffer_;
		void* const_map_;
		static void StaticGraphicInit(Game& game);
		void NonstaticGraphicInit(Game& game);
	};

}
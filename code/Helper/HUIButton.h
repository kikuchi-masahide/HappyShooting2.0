#pragma once
#include "../Engine/Game.h"

class UIScreen;

namespace Helpers {
	class HUIButton
	{
	public:
		/// <param name="texture_away">マウスがボタン上にないときのテクスチャ</param>
		/// <param name="texture_over">マウスがボタン上にあるときのテクスチャ</param>
		/// <param name="centerx">ボタンの中心x座標</param>
		/// <param name="width">ボタンのx座標幅</param>
		/// <param name="centery">ボタンの中心y座標</param>
		/// <param name="height">ボタンのy座標高さ</param>
		/// <param name="action">ボタンが押されたときのアクション</param>
		HUIButton(UIScreen* screen, unsigned int texture_away, unsigned int texture_over, double centerx, double width, double centery, double height, std::function<void(HUIButton* button)> action);
		~HUIButton();
		void Update();
		void Output();
		UIScreen* const screen_;
	private:
		static boost::shared_ptr<DX12GraphicsPipeline> pipeline_;
		static boost::shared_ptr<DX12RootSignature> root_signature_;
		//マウスが上に無い時とある時でヒープを使い分ける
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
		//クリック時(ボタン上で左ボタンが離された)の動作
		std::function<void(HUIButton* button)> click_action_;
		//Updateで更新
		bool is_mouse_over_;
	};
}

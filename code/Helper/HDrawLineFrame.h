#pragma once
#include "../Engine/Game.h"

namespace Helpers {

	//レンダーターゲットがセットされた状態で，指定座標に指定角度で枠線を描く
	class HDrawLineFrame
	{
	public:
		HDrawLineFrame(Game& game);
		/// <summary>
		/// レンダーターゲットがセットされた状態で，中心と回転角度を指定して枠線を描画する
		/// </summary>
		/// <param name="center_x">レンダーターゲット中心が原点のときの，フレーム中心x[px]</param>
		/// <param name="center_y">レンダーターゲット中心が原点のときの，フレーム中心y[px]</param>
		/// <param name="rt_width">レンダーターゲット幅</param>
		/// <param name="rt_height">レンダーターゲット高さ</param>
		/// <param name="color">枠線の色(省略時不透明黒色)</param>
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
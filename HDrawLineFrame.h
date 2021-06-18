#pragma once
#include "Game.h"

//レンダーターゲットがセットされた状態で，指定座標に指定角度で枠線を描く
class HDrawLineFrame
{
public:
	HDrawLineFrame(Game& game);
	/// <summary>
	/// レンダーターゲットがセットされた状態で，中心と回転角度を指定して枠線を描画する
	/// </summary>
	/// <param name="rt_width">レンダーターゲット幅</param>
	/// <param name="rt_height">レンダーターゲット高さ</param>
	void DrawFrame(Game& game, double center_x, double center_y, double width,double height,double angle, unsigned int rt_width, unsigned int rt_height);
private:
	static boost::shared_ptr<DX12GraphicsPipeline> pipeline_;
	static boost::shared_ptr<DX12Resource> vertex_buffer_;
	static boost::shared_ptr<DX12RootSignature> root_signature_;
	static void GraphicInit(Game& game);
};


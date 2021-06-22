#pragma once
#include "Game.h"

/// <summary>
/// テクスチャをαと角度を指定して描画する
/// </summary>
class HTextureAlphaRotateDraw
{
public:
	HTextureAlphaRotateDraw(Game& game, unsigned int textureid);
	/// <summary>
	/// RTVを開いた状態で，指定座標に指定角度だけ回転して指定αでテクスチャを描く
	/// </summary>
	/// <param name="center_x">中心座標x[px]</param>
	/// <param name="center_y">中心座標y[px]</param>
	/// <param name="width">テクスチャ幅を何pxにするか</param>
	/// <param name="height">テクスチャ高さを何pxにするか</param>
	/// <param name="angle">反時計回りで回転角度[rad]</param>
	/// <param name="alpha">不透明度</param>
	/// <param name="rt_width">レンダーターゲット幅</param>
	/// <param name="rt_height">レンダーターゲット高さ</param>
	void Draw(Game& game, double center_x, double center_y, double width, double height, double angle, double alpha, double rt_width, double rt_height);
private:
	static boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
	static boost::shared_ptr<DX12RootSignature> rootsignature_;
	static boost::shared_ptr<DX12Resource> vertex_buffer_;
	static boost::shared_ptr<DX12Resource> index_buffer_;
	//シェーダーに渡す情報のリソース
	boost::shared_ptr<DX12Resource> info_to_shader_;
	//info_to_shader_のビュー入りヒープ
	boost::shared_ptr<DX12DescriptorHeap> info_crv_heap_;
	//テクスチャのsrv
	boost::shared_ptr<DX12DescriptorHeap> srv_heap_;
	//ビューがヒープのどこに入っているか
	unsigned int srv_heap_ind_;
	//テクスチャID
	unsigned int texture_id_;
	//テクスチャの大きさ
	double tex_width_;
	double tex_height_;
	//不透明度マップ先
	float* alpha_map_;
	//頂点バッファの1頂点情報
	struct Vertex {
	public:
		float x, y, z;
		float u, v;
		Vertex(double _x, double _y, double _z, double _u, double _v)
			:x(_x), y(_y), z(_z), u(_u), v(_v) {}
	};
	//staticなグラフィック関連変数の初期化
	void static StaticGraphicInit(Game& game);
	//非staticなグラフィック関連変数の初期化
	void NonstaticGraphicsInit(Game& game);
};


#pragma once
#include "../Engine/Game.h"

namespace Helpers {

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
		/// <param name="center_x">RTV中心を原点としたときの，テクスチャ中心座標x[px]</param>
		/// <param name="center_y">RTV中心を原点としたときの，テクスチャ中心座標y[px]</param>
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
		boost::shared_ptr<DX12DescriptorHeap> desc_heap_;
		//ビューがヒープのどこに入っているか
		unsigned int srv_heap_ind_;
		//テクスチャID
		unsigned int texture_id_;
		//テクスチャの大きさ
		double tex_width_;
		double tex_height_;
		//シェーダに渡す情報のマップ先
		void* info_to_shader_map_;
		//staticなグラフィック関連変数の初期化
		void static StaticGraphicInit(Game& game);
		//非staticなグラフィック関連変数の初期化
		void NonstaticGraphicsInit(Game& game);
	};

}
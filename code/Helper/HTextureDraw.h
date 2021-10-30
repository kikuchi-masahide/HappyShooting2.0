#pragma once
#include "../Game.h"

namespace Helpers {

	//テクスチャの描画を指定座標に行うヘルパ
	//RTVを開いた状態でないといけない
	class HTextureDraw
	{
	public:
		/// <param name="_textureid">このインスタンスで描くテクスチャのID</param>
		HTextureDraw(Game& _game, unsigned int _textureid);
		/// <summary>
		/// RTVを開いた状態で，指定座標にテクスチャを描く
		/// </summary>
		/// <param name="_lx">左端x(レンダーターゲット中心が原点)[px]</param>
		/// <param name="_rx">右端x(レンダーターゲット中心が原点)[px]</param>
		/// <param name="_by">下端y(レンダーターゲット中心が原点)[px]</param>
		/// <param name="_ty">上端y(レンダーターゲット中心が原点)[px]</param>
		/// <param name="_rtwidth">レンダーターゲットの横幅[px]</param>
		/// <param name="_rtheight">レンダーターゲットの縦幅[px]</param>
		void DrawInRect(Game& _game, double _lx, double _rx, double _by, double _ty, unsigned int _rtwidth, unsigned int _rtheight);
		/// <summary>
		/// RTVを開いた状態で，中心点と倍率を指定してテクスチャを描く
		/// </summary>
		/// <param name="_cx">中心x(レンダーターゲット中心が原点)[px]</param>
		/// <param name="_cy">中心y(レンダーターゲット中心が原点)[px]</param>
		/// <param name="_rx">幅[px]</param>
		/// <param name="_ry">高さ[px]</param>
		/// <param name="_rtwidth">レンダーターゲットの横幅[px]</param>
		/// <param name="_rtheight">レンダーターゲットの縦幅[px]</param>
		void DrawCenter(Game& _game, double _cx, double _cy, double _rx, double _ry, unsigned int _rtwidth, unsigned int _rtheight);
	private:
		static boost::shared_ptr<DX12GraphicsPipeline> mGPipeline;
		static boost::shared_ptr<DX12RootSignature> mRootSignature;
		static boost::shared_ptr<DX12Resource> mIndexBuffer;
		static boost::shared_ptr<DX12Resource> mVertexBuffer;
		//拡大・平行移動用の定数バッファとそのビューのためのヒープ
		boost::shared_ptr<DX12Resource> mMatrixBuffer;
		boost::shared_ptr<DX12DescriptorHeap> mDescHeap;
		//パイプライン等の初期化
		static void StaticGraphicInit(Game& _game);
		void InitializeDescHeap(Game& _game, unsigned int _textureid);
		//コンストラクタで呼び出され，定数バッファとそのCRVの初期化を行う
		void InitializeConstBuffer(Game& game);
		struct Vertex {
		public:
			XMFLOAT3 pos_;
			XMFLOAT2 uv_;
		};
		//テクスチャの大きさ
		double texWidth_;
		double texHeight_;
		//行列マップ先
		void* matrix_map;
	};

}
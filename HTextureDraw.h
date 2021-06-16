#pragma once
#include "Game.h"

//テクスチャの描画を指定座標に行うヘルパ
//RTVを開いた状態でないといけない
class HTextureDraw
{
public:
	/// <param name="_textureid">このインスタンスで描くテクスチャのID</param>
	HTextureDraw(Game& _game,unsigned int _textureid);
	/// <summary>
	/// RTVを開いた状態で，指定座標にテクスチャを描く
	/// </summary>
	/// <param name="_lx">左端x[px]</param>
	/// <param name="_rx">右端x[px]</param>
	/// <param name="_by">下端y[px]</param>
	/// <param name="_ty">上端y[px]</param>
	/// <param name="_rtwidth">レンダーターゲットの横幅[px]</param>
	/// <param name="_rtheight">レンダーターゲットの縦幅[px]</param>
	void DrawInRect(Game& _game, double _lx, double _rx, double _by, double _ty, unsigned int _rtwidth,unsigned int _rtheight);
	/// <summary>
	/// RTVを開いた状態で，中心点と倍率を指定してテクスチャを描く
	/// </summary>
	/// <param name="_cx">中心x[px]</param>
	/// <param name="_cy">中心y[px]</param>
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
	boost::shared_ptr<DX12DescriptorHeap> mCRVDescHeap;
	//パイプライン等の初期化
	static void GraphicInit(Game& _game);
	//コンストラクタで呼び出されSRVの読み込みを行う
	void ReadSRV(Game& _game,unsigned int _textureid);
	//コンストラクタで呼び出され，定数バッファとそのCRVの初期化を行う
	void InitializeCRV(Game& game);
	struct Vertex {
	public:
		float x, y, z;
		float u, v;
		Vertex(float _x, float _y, float _z, float _u, float _v)
			:x(_x),y(_y),z(_z),u(_u),v(_v){}
	};
	//SRVの入っているヒープとその番号
	boost::shared_ptr<DX12DescriptorHeap> mSRVHeap;
	unsigned int mSRVHeapIndex;
	//テクスチャの大きさ
	double texWidth_;
	double texHeight_;
	//行列マップ先
	void* matrix_map;
};
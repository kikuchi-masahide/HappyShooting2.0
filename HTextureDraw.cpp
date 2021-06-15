#include "HTextureDraw.h"

void HTextureDraw::Draw(Game* _game, double _lx, double _rx, double _by, double _ty, unsigned int _rtwidth, unsigned int _rtheight)
{
	//変形行列をセットする
	//座標を-1~1に変換
	_lx = 2 * _lx / _rtwidth - 1;
	_rx = 2 * _rx / _rtwidth - 1;
	_ty = 2 * _ty / _rtheight - 1;
	_by = 2 * _by / _rtheight - 1;
	//拡大
	MatVec::Matrix4d mat = MatVec::Expand(_rx - _lx, _ty - _by, 1);
	//平行移動
	mat = MatVec::Translation((_lx + _rx) / 2, (_by + _ty) / 2, 0) * mat;
	//定数バッファにマップ
	void* map = _game->mdx12.Map(mMatrixBuffer);
	_game->mdx12.Copy4x4Matrix(map, mat);
	_game->mdx12.Unmap(mMatrixBuffer);
	//パイプライン
	_game->mdx12.SetGraphicsPipeline(mGPipeline);
	//ルートシグネチャ
	_game->mdx12.SetRootSignature(mRootSignature);
	//ディスクリプタヒープのセット
	_game->mdx12.SetDescriptorHeap(mSRVHeap);
	_game->mdx12.SetDescriptorHeap(mCRVDescHeap);
	_game->mdx12.SetGraphicsRootDescriptorTable(0, mSRVHeap, mSRVHeapIndex);
	_game->mdx12.SetGraphicsRootDescriptorTable(1, mCRVDescHeap, 0);
	//プリミティブトポロジ
	_game->mdx12.SetPrimitiveTopology(DX12Config::PrimitiveTopology::TRIANGLESTRIP);
	//頂点バッファ指定
	_game->mdx12.SetVertexBuffers(mVertexBuffer, 0, sizeof(Vertex) * 4, sizeof(Vertex));
	//インデックスバッファ
	_game->mdx12.SetIndexBuffers(mIndexBuffer, 6);
	//ビューポート
	_game->mdx12.SetViewports(900, 900, 0, 0, 1.0f, 0.0f);
	_game->mdx12.SetScissorrect(0, 900, 0, 900);
	//描画
	_game->mdx12.DrawIndexedInstanced(6, 1, 0, 0, 0);
}

HTextureDraw::HTextureDraw(Game* _game, unsigned int _textureid)
{
	//初期設定が終わっていない場合のみ呼び出す
	if (mGPipeline == nullptr)
	{
		GraphicInit(_game);
	}
	ReadSRV(_game,_textureid);
}

void HTextureDraw::GraphicInit(Game* _game)
{
	//ルートパラメータ
	DX12RootParameter rootparam;
	rootparam.mShaderVisibility = DX12Config::RootParameterShaderVisibility::ALL;
	//SRV
	rootparam.mDescRanges.push_back(DX12DescriptorRange(
		1, DX12Config::DescriptorRangeType::SRV, 0
	));
	//CBV
	rootparam.mDescRanges.push_back(DX12DescriptorRange(
		1, DX12Config::DescriptorRangeType::CBV, 0
	));
	//ルートシグネチャ
	mRootSignature = _game->mdx12.CreateRootSignature(rootparam);
	//インデックスバッファ
	mIndexBuffer = _game->mdx12.CreateIndexBuffer(6);
	unsigned int* indexmap = (unsigned int*)_game->mdx12.Map(mIndexBuffer);
	//0 3
	//1 2
	indexmap[0] = 0;
	indexmap[1] = 1;
	indexmap[2] = 3;
	indexmap[3] = 1;
	indexmap[4] = 2;
	indexmap[5] = 3;
	_game->mdx12.Unmap(mIndexBuffer);
	//頂点バッファ
	mVertexBuffer = _game->mdx12.CreateVertexBuffer(sizeof(Vertex) * 4);
	Vertex* vertexmap = (Vertex*)_game->mdx12.Map(mVertexBuffer);
	vertexmap[0] = Vertex(-0.5, 0.5, 0.0, 0.0, 0.0);
	vertexmap[1] = Vertex(-0.5, -0.5, 0.0, 0.0, 1.0);
	vertexmap[2] = Vertex(0.5, -0.5, 0.0, 1.0, 1.0);
	vertexmap[3] = Vertex(0.5, 0.5, 0.0, 1.0, 0.0);
	_game->mdx12.Unmap(mVertexBuffer);
	//シェーダー取得
	auto vertexshader = _game->mShaderManager.GetDX12ShaderObject(0);
	auto pixelshader = _game->mShaderManager.GetDX12ShaderObject(1);
	//頂点レイアウト
	DX12VertexLayout vertexlayout;
	vertexlayout.push_back(DX12VertexLayoutUnit(
		"POS", DX12Config::VertexLayoutFormat::R32G32B32_FLOAT,0,DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
	));
	vertexlayout.push_back(DX12VertexLayoutUnit(
		"UV", DX12Config::VertexLayoutFormat::R32G32_FLOAT, 0, DX12Config::VertexLayoutInputClassification::INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	));
	//パイプライン作成
	mGPipeline = _game->mdx12.CreateGraphicsPipeline(
		vertexshader, pixelshader, vertexlayout, DX12Config::PrimitiveTopologyType::TRIANGLE, 1, mRootSignature
	);
	//定数バッファ作成
	mMatrixBuffer = _game->mdx12.CreateConstBuffer(DX12Config::ResourceHeapType::UPLOAD,sizeof(double)*16);
	//定数バッファのヒープ
	mCRVDescHeap = _game->mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 1);
	//定数バッファのビュー
	_game->mdx12.CreateConstBufferView(mMatrixBuffer, mCRVDescHeap, 0);
}

void HTextureDraw::ReadSRV(Game* _game, unsigned int _textureid)
{
	auto res = _game->mTexManager.GetDX12DescriptorHeap(_textureid);
	mSRVHeap = res.first;
	mSRVHeapIndex = res.second;
}

boost::shared_ptr<DX12GraphicsPipeline> HTextureDraw::mGPipeline = nullptr;
boost::shared_ptr<DX12RootSignature> HTextureDraw::mRootSignature = nullptr;
boost::shared_ptr<DX12Resource> HTextureDraw::mIndexBuffer = nullptr;
boost::shared_ptr<DX12Resource> HTextureDraw::mVertexBuffer = nullptr;
boost::shared_ptr<DX12Resource> HTextureDraw::mMatrixBuffer = nullptr;
boost::shared_ptr<DX12DescriptorHeap> HTextureDraw::mCRVDescHeap = nullptr;
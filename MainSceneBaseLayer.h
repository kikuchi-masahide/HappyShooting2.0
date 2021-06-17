#pragma once
#include "Layer.h"
#include "ComponentHandle.h"
#include "MainSceneDrawComponent.h"

class MainSceneBaseLayer :public Layer
{
public:
	MainSceneBaseLayer(Scene* scene, boost::shared_ptr<std::set<void*>> hset);
	virtual ~MainSceneBaseLayer();
	void Draw();
	/// <summary>
	/// Draw()から呼び出される，ペラポリゴンを実際にウィンドウへ描画するための関数
	/// ペラポリゴンは，全componentの描画が済んだ状態になっており，シェーダーリソース状態にするバリア実行済
	/// </summary>
	virtual void UniqueDraw() = 0;
	/// <summary>
	/// MainSceneからアクティブになる前のtickに呼び出される．このレイヤーをアクティブにする
	/// (アクティブな状態で呼び出されるとカウンタリセットし0の状態からスタート)
	/// </summary>
	void SetActive();
	void SetUnActive();
	/// <summary>
	/// MainSceneから呼び出される，Drawコールが必要なコンポーネントの追加関数
	/// </summary>
	void AddComponent(ComponentHandle<MainSceneDrawComponent> component);
private:
	std::vector<ComponentHandle<MainSceneDrawComponent>> draw_components_;
	//このレイヤーがアクティブか否か
	bool is_active_;
	//このレイヤーがアクティブになってから何度目のフレームか
	//(1回目にUniqueDrawが呼び出されたときが0)
	unsigned int layer_t_;
	//ペラポリゴン
	boost::shared_ptr<DX12Resource> pera_texture_;
	//ペラポリゴンのRTV;
	boost::shared_ptr<DX12DescriptorHeap> pera_rtv_;
	//ペラポリゴンのSRV;
	boost::shared_ptr<DX12DescriptorHeap> pera_srv_;
	//MainSceneBaseLayerのグラフィックス初期化
	void GraphicsInit();
};
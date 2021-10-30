#pragma once
#include "../Engine/Layer.h"
#include "../Engine/Game.h"
#include "../Engine/Component.h"

class MainSceneDrawComponent;
class MyselfPosAndAngleComponent;

//draw_components_で保存するときのためのクラス
class DrawComponentUnit
{
public:
	DrawComponentUnit(ComponentHandle<MainSceneDrawComponent> handle);
	ComponentHandle<MainSceneDrawComponent> handle_;
	double z_;
};

//draw_components_用の比較関数
class DrawComponentCompare {
public:
	bool operator()(const DrawComponentUnit& left, const DrawComponentUnit& right) const
	{
		return left.z_ < right.z_;
	}
};

class MainSceneBaseLayer :public Layer
{
public:
	MainSceneBaseLayer(Scene* scene);
	virtual ~MainSceneBaseLayer();
	void Draw() final;
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
	/// <summary>
	/// layer_t_(アクティブになってからの時間)を取得
	/// </summary>
	unsigned int GetLayert();
	/// <summary>
	/// このレイヤーの変形行列を受け取る(activeな時のみ呼び出されうる)
	/// </summary>
	/// <returns></returns>
	virtual MatVec::Matrix4x4 GetLayerTransform() = 0;
protected:
	//ペラポリゴン
	boost::shared_ptr<DX12Resource> pera_texture_;
	//ペラポリゴンのRTV;
	boost::shared_ptr<DX12DescriptorHeap> pera_rtv_;
	//ペラポリゴンのSRV;
	boost::shared_ptr<DX12DescriptorHeap> pera_srv_;
	Game& GetGame();
	Scene* const scene_;
private:
	std::multiset<DrawComponentUnit,DrawComponentCompare> draw_components_;
	//このレイヤーがアクティブになってから何度目のフレームか
	//(1回目にUniqueDrawが呼び出されたときが0)
	unsigned int layer_t_;
	//このレイヤーがアクティブか否か
	bool is_active_;
	//MainSceneBaseLayerのグラフィックス初期化
	void GraphicsInit();
};
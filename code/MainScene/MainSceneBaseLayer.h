#pragma once
#include "../Engine/Layer.h"
#include "../Engine/Game.h"
#include "../Engine/Component.h"

class MainSceneDrawComponent;
class DrawComponentUnit;
class DrawComponentCompare;
using DrawComponentsMultiset = std::multiset<DrawComponentUnit, DrawComponentCompare>;
class MyselfPosAndAngleComponent;
//内部カウンタをUpdate毎に増やすため
template<class T>
class AddOneComponent;

class MainSceneBaseLayer :public Layer
{
public:
	MainSceneBaseLayer(Scene* scene, DrawComponentsMultiset* draw_components);
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
	/// layer_t_(アクティブになってからの時間)を取得
	/// </summary>
	int GetLayert();
	/// <summary>
	/// レイヤーの中心(左下中心ならば座標(300,450)の点)を原点とする、レイヤーの変形行列を受け取る(activeな時のみ呼び出されうる)
	/// すなわち、レイヤーの任意の点x(=(x,y,z,1)^t)がx'に移動するとき、x'=Axとなる行列Aを返す
	/// </summary>
	/// <returns></returns>
	virtual MatVec::Matrix4x4 GetLayerTransform() = 0;
	//このレイヤーがアクティブになってから何度目のフレームか
	//(1回目にUniqueDrawが呼び出されたときが0)
	int layer_t_;
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
	//Drawで呼び出すcomponent群
	DrawComponentsMultiset* draw_components_;
	//このレイヤーがアクティブか否か
	bool is_active_;
	//MainSceneBaseLayerのグラフィックス初期化
	void GraphicsInit();
	//Update毎にlayer_t_++;する
	GameObjectHandle addone_obj_;
	ComponentHandle<AddOneComponent<int>> addone_comp_;
};
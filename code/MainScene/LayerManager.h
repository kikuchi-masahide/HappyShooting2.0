#pragma once
#include "MainSceneBaseLayer.h"
#include "../Engine/Layer.h"
#include "Math.h"
#include "../Engine/Component.h"

class MainSceneDrawComponent;
class Scene;

//draw_components_の保存単位
//(MainSceneDrawComponent挿入時，multisetのいくつかのcomponentは消去された状態で起こっているため，あらかじめzを保存しておく)
class DrawComponentUnit {
public:
	DrawComponentUnit(ComponentHandle<MainSceneDrawComponent> comp);
	ComponentHandle<MainSceneDrawComponent> comp_;
	double z_;
};

//draw_components_用の比較関数
class DrawComponentCompare {
public:
	bool operator()(const DrawComponentUnit& left, const DrawComponentUnit& right) const;
};
using DrawComponentsMultiset = std::multiset<DrawComponentUnit, DrawComponentCompare>;

class LayerManager
{
public:
	LayerManager(Scene* scene);
	~LayerManager();
	//諸レイヤーの初期化をまとめて行う
	//TODO:コンストラクタで初期化をできた方がよさげな気がするが，自機ハンドルの渡す順などの関係でどうしても後に回さざるを得ない 不愉快
	void InitLayers();
	/// <summary>
	/// 今アクティブなレイヤーに描画コンポーネントを追加
	/// </summary>
	void AddComponentToLayer(ComponentHandle<MainSceneDrawComponent> component);
	/// <summary>
	/// 次tickからこのフレームを有効化する
	/// </summary>
	void SwapLayer(unsigned int ind);
	/// <summary>
	/// 現在有効なレイヤーの変形行列を得る
	/// </summary>
	MatVec::Matrix4x4 GetLayerTransform();
	/// <summary>
	/// SceneのPriorUniqueUpdateで呼び出してもらう
	/// </summary>
	void PriorUniqueUpdate();
	//親Scene(MainSceneDrawComponent等が使えるように)
	Scene* const scene_;
	//このオブジェクトを自機として指定
	void SetMyselfHandle(GameObjectHandle handle);
private:
	//持っているレイヤーの内描画するもの
	LayerHandle<MainSceneBaseLayer> active_layer_;
	//使えるレイヤーの一覧
	LayerHandle<MainSceneBaseLayer> available_layers_[5];
	//次のtickから使うレイヤー(none:999)
	unsigned int layer_from_next_tick_;
	GameObjectHandle myself_;
	//呼び出すDrawComponents_のmultiset
	DrawComponentsMultiset draw_components_;
};


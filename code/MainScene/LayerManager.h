#pragma once
#include "MainSceneBaseLayer.h"
#include "../Engine/Layer.h"
#include "Math.h"
#include "../Engine/Component.h"

class MainSceneDrawComponent;
class Scene;

class LayerManager
{
public:
	LayerManager(Scene* scene);
	~LayerManager();
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
private:
	//持っているレイヤーの内描画するもの
	LayerHandle<MainSceneBaseLayer> active_layer_;
	//使えるレイヤーの一覧
	LayerHandle<MainSceneBaseLayer> available_layers_[1];
	//次のtickから使うレイヤー(none:999)
	unsigned int layer_from_next_tick_;
};


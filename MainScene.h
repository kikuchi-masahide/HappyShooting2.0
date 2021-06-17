#pragma once
#include "Scene.h"
#include "LayerHandle.h"
#include "MainSceneBaseLayer.h"

class MainScene :public Scene
{
public:
	MainScene(Game* game);
	void UniqueUpdate();
	void UniqueOutput();
	~MainScene();
	/// <summary>
	/// 今アクティブなレイヤーに描画コンポーネントを追加
	/// </summary>
	void AddComponentToLayer(ComponentHandle<MainSceneDrawComponent> component);
	/// <summary>
	/// 次tickからこのフレームを有効化する
	/// </summary>
	void SwapLayer(unsigned int ind);
private:
	//持っているレイヤーの内描画するもの
	LayerHandle<MainSceneBaseLayer> active_layer_;
	//使えるレイヤーの一覧
	LayerHandle<MainSceneBaseLayer> available_layers_[1];
	//次のtickから使うレイヤー(none:999)
	unsigned int layer_from_next_tick_;
};
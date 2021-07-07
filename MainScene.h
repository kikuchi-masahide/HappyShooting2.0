#pragma once
#include "Scene.h"
#include "LayerHandle.h"
#include "MainSceneBaseLayer.h"
#include "CollisionManager.h"

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
	//自機が含まれる方のCollisionManager
	CollisionManager collision_myself_;
	//敵機が含まれる方のCollisionManager
	CollisionManager collision_enemy_;
	//スコアを加算
	void AddScore(int add);
	int GetScore() const;
private:
	//持っているレイヤーの内描画するもの
	LayerHandle<MainSceneBaseLayer> active_layer_;
	//使えるレイヤーの一覧
	LayerHandle<MainSceneBaseLayer> available_layers_[1];
	//次のtickから使うレイヤー(none:999)
	unsigned int layer_from_next_tick_;
	//自機オブジェクトのハンドル
	GameObjectHandle myself_handle_;
	//自機の位置角度変更コンポーネント
	ComponentHandle<MyselfPosAndAngleComponent> myself_pos_angle_handle_;
	//シーンに自機を追加する
	void AddMyself();
	//現在のスコア
	int score_;
};
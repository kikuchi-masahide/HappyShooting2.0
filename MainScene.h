#pragma once
#include "Scene.h"
#include "LayerHandle.h"
#include "MainSceneBaseLayer.h"
#include "CollisionManager.h"

class MainScene :public Scene
{
public:
	MainScene(Game* game);
	void PriorUniqueUpdate() override;
	void PosteriorUniqueUpdate() override;
	void PriorUniqueOutput() override;
	void PosteriorUniqueOutput() override;
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
	CollisionManager collision_manager_;
	//スコアを加算
	void AddScore(int add);
	int GetScore() const;
	/// <summary>
	/// 自機が狙いうる敵機の追加
	/// </summary>
	// TEST:敵機を追加したらテスト
	void AddDirectableEnemy(GameObjectHandle enemy);
	/// <summary>
	/// 自機から最も近い敵機を返す(誰もいないならnull)
	/// </summary>
	GameObjectHandle GetNearestEnemy();
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
	std::list<GameObjectHandle> enemies_;
	//前フレーム終了時での，自機に最も近かった敵機
	GameObjectHandle nearest_enemy_;
	//フレーム終わりで時期に最も近い敵機を見つける
	void FindNearestEnemy();
	//enemy1群のみこちらで準備する
	void PrepareEnemy1();
};
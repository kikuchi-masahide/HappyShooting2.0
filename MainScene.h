#pragma once
#include "Scene.h"
#include "LayerHandle.h"
#include "MainSceneBaseLayer.h"
#include "CollisionManager.h"
#include "LayerManager.h"
#include "ScoreManager.h"
#include "EnemyWaveManager.h"

class MainScene :public Scene
{
public:
	MainScene(Game* game);
	void PriorUniqueUpdate() override;
	void PosteriorUniqueUpdate() override;
	void PriorUniqueOutput() override;
	void PosteriorUniqueOutput() override;
	~MainScene();
	//自機が含まれる方のCollisionManager
	CollisionManager collision_manager_;
	/// <summary>
	/// 自機が狙いうる敵機の追加
	/// </summary>
	// TEST:敵機を追加したらテスト
	void AddDirectableEnemy(GameObjectHandle enemy);
	/// <summary>
	/// 自機から最も近い敵機を返す(誰もいないならnull)
	/// </summary>
	GameObjectHandle GetNearestEnemy();
	//TODO:そのうち消す?
	boost::shared_ptr<LayerManager> GetLayerManager();
	//TODO:そのうち消す?
	boost::shared_ptr<ScoreManager> GetScoreManager();
	//自機オブジェクトのハンドル
	GameObjectHandle myself_handle_;
private:
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
	boost::shared_ptr<LayerManager> layer_manager_;
	boost::shared_ptr<ScoreManager> score_manager_;
	boost::shared_ptr<EnemyWaveManager> enemy_wave_manager_;
};
#pragma once
#include "../Engine/Scene.h"
#include "../Engine/Layer.h"
#include "MainSceneBaseLayer.h"
#include "CollisionManager.h"
#include "LayerManager.h"
#include "ScoreManager.h"
#include "EnemyWaveManager.h"

class MyselfMediatorComponent;

class MainScene :public Scene
{
public:
	MainScene(Game* game);
	void PriorUniqueUpdate() override;
	void PosteriorUniqueUpdate() override;
	void PriorUniqueOutput() override;
	void PosteriorUniqueOutput() override;
	~MainScene();
	boost::shared_ptr<LayerManager> GetLayerManager();
	boost::shared_ptr<ScoreManager> GetScoreManager();
	boost::shared_ptr<EnemyWaveManager> GetEnemyWaveManager();
	boost::shared_ptr<CollisionManager> GetCollisionManager();
	GameObjectHandle GetMyselfHandle();
	void SetMyselfArmor2();
	void AddLife(int n);
	//自機のメディエータ
	ComponentHandle<MyselfMediatorComponent> mediator_;
private:
	//シーンに自機を追加する
	void AddMyself();
	//現在のスコア
	int score_;
	std::list<GameObjectHandle> enemies_;
	//前フレーム終了時での，自機に最も近かった敵機
	GameObjectHandle nearest_enemy_;
	boost::shared_ptr<LayerManager> layer_manager_;
	boost::shared_ptr<ScoreManager> score_manager_;
	boost::shared_ptr<EnemyWaveManager> enemy_wave_manager_;
	boost::shared_ptr<CollisionManager> collision_manager_;
};
#include "MainScene.h"

#include "MainSceneBasicLayer.h"
#include "MainSceneUIScreen.h"
#include "DrawTextureComponent.h"
#include "MyselfPosAndAngleComponent.h"
#include "MyselfMediatorComponent.h"
#include "DrawNormalBulletComponent.h"
#include "EnemyWaveManager.h"
#include "CollisionUIScreen.h"
#include "EnemyWave6.h"

MainScene::MainScene(Game* game)
	:Scene(game)
{
	Log::OutputTrivial("start MainScene;");
	//レイヤー
	layer_manager_ = boost::shared_ptr<LayerManager>(DBG_NEW LayerManager(this));
	//スコア
	score_manager_ = boost::shared_ptr<ScoreManager>(DBG_NEW ScoreManager);


	////enemy1群追加
	//PrepareEnemy1();


	//UIScreen
	AddUIScreen<MainSceneUIScreen>(score_manager_);

	CollisionUIScreen* collision_ui = AddUIScreen<CollisionUIScreen>();
	collision_manager_ = boost::shared_ptr<CollisionManager>(DBG_NEW CollisionManager(collision_ui));

	//自機追加
	AddMyself();
	layer_manager_->SetMyselfHandle(myself_handle_);
	layer_manager_->InitLayers();

	enemy_wave_manager_ = boost::shared_ptr<EnemyWaveManager>(DBG_NEW EnemyWaveManager(this));
	enemy_wave_manager_->SetWave(boost::shared_ptr<EnemyWaveBase>(DBG_NEW EnemyWave6(this)));
}

void MainScene::PriorUniqueUpdate()
{
	//レイヤーの入れ替え
	layer_manager_->PriorUniqueUpdate();
}

void MainScene::PosteriorUniqueUpdate()
{
	//全Updateが終わったあと当たり判定だけ処理させ，死ぬべきオブジェクトを死なせる
	collision_manager_->TraverseAll();
	enemy_wave_manager_->Update();
}

void MainScene::PriorUniqueOutput()
{
}

void MainScene::PosteriorUniqueOutput()
{
}

MainScene::~MainScene()
{
	Log::OutputTrivial("end MainScene;");
}

boost::shared_ptr<LayerManager> MainScene::GetLayerManager()
{
	return layer_manager_;
}

boost::shared_ptr<ScoreManager> MainScene::GetScoreManager()
{
	return score_manager_;
}

boost::shared_ptr<EnemyWaveManager> MainScene::GetEnemyWaveManager()
{
	return enemy_wave_manager_;
}

boost::shared_ptr<CollisionManager> MainScene::GetCollisionManager()
{
	return collision_manager_;
}

GameObjectHandle MainScene::GetMyselfHandle()
{
	return myself_handle_;
}

void MainScene::AddMyself()
{
	myself_handle_ = AddObject(MatVec::Vector2(0, -275), 1.0, 0.0);
	//他のコンポーネントの追加はメディエータに任せる
	myself_handle_->AddUpdateComponent<MyselfMediatorComponent>(layer_manager_,score_manager_,collision_manager_);
}

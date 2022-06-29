#include "EnemyWave45.h"

#include "EnemyWaveManager.h"
#include "MainScene.h"
#include "Enemy5MoveComponent.h"
#include "DrawTextureComponent.h"
#include "EnemyHealthComponent.h"
#include "Enemy3CollisionComponent.h"
#include "DrawHealthBarComponent.h"
#include "Enemy5ShootComponent.h"
#include "Enemy4BehaviorComponent.h"
#include "EnemyWaveBoss1.h"

EnemyWave45::EnemyWave45(MainScene* main_scene)
	:EnemyWaveBase(120, main_scene)
{
	Log::OutputTrivial("start EnemyWave45;");
	auto scene = main_scene;
	auto myself = scene->GetMyselfHandle();
	auto enemywaveman = main_scene->GetEnemyWaveManager();
	for (int i = 0; i < 8; i++)
	{
		auto obj = scene->AddObject(MatVec::Vector2(0.0, 900.0), 1.0, 0.0);
		obj->AddUpdateComponent<Enemy5MoveComponent>(-30 * (i+6));
		auto draw = obj->AddOutputComponent<DrawTextureComponent>(scene->GetLayerManager(), 8, -5);
		draw->width_ = 40;
		draw->height_ = 40;
		auto health = obj->AddUpdateComponent<EnemyHealthComponent>(scene->GetLayerManager(), 600);
		//Enemy3‚ÆŒ`‚ªˆê‚È‚Ì‚Å“–‚½‚è”»’è‚àˆê
		obj->AddUpdateComponent<Enemy3CollisionComponent>(scene->GetCollisionManager(), scene->GetScoreManager(), health);
		obj->AddOutputComponent<DrawHealthBarComponent<EnemyHealthComponent>>(scene->GetLayerManager(), health, MatVec::Vector2(0, 30));
		obj->AddUpdateComponent<Enemy5ShootComponent>(50, scene->GetMyselfHandle(), 10, 4, 60, -30 * (i + 6), 100, scene->GetLayerManager(), scene->GetCollisionManager());
		enemywaveman->AddEnemyInWave(obj);
	}
	auto enemy4_1 = scene->AddObject(MatVec::Vector2(0.0, 900.0), 1.0, 0.0);
	enemy4_1->AddUpdateComponent<Enemy4BehaviorComponent>(scene->GetCollisionManager(), scene->GetLayerManager(), scene->GetScoreManager(), myself, 1);
	enemywaveman->AddEnemyInWave(enemy4_1);
	auto enemy4_2 = scene->AddObject(MatVec::Vector2(0.0, 900.0), 1.0, 0.0);
	enemy4_2->AddUpdateComponent<Enemy4BehaviorComponent>(scene->GetCollisionManager(), scene->GetLayerManager(), scene->GetScoreManager(), myself, -1);
	enemywaveman->AddEnemyInWave(enemy4_2);
}

EnemyWave45::~EnemyWave45()
{
	Log::OutputTrivial("end EnemyWave45;");
}

void EnemyWave45::OnDelete()
{
	main_scene_->GetEnemyWaveManager()->SetWave(boost::shared_ptr<EnemyWaveBase>(DBG_NEW EnemyWaveBoss1(main_scene_)));
}

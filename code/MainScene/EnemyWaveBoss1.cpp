#include "EnemyWaveBoss1.h"

#include "EnemyWaveManager.h"
#include "MainScene.h"
#include "Boss1MediatorComponent.h"
#include "Boss1StateEntering.h"
#include "BossIncomingUpdate.h"

EnemyWaveBoss1::EnemyWaveBoss1(MainScene* main_scene)
	:EnemyWaveBase(120,main_scene)
{
	auto boss = main_scene->AddObject(MatVec::Vector2(0, 900), 1.0, 0.0);
	auto mediator = boss->AddUpdateComponent<Boss1MediatorComponent>(
		main_scene->GetLayerManager(), main_scene->GetScoreManager(), main_scene->GetEnemyWaveManager(), main_scene->GetCollisionManager()
		);
	mediator->ChangeState(DBG_NEW Boss1StateEntering(mediator, main_scene->GetLayerManager(), main_scene->GetScoreManager(), main_scene->GetCollisionManager(), main_scene->GetEnemyWaveManager()));
	auto boss_incoming_obj = main_scene->AddObject(MatVec::Vector2(), 1.0, 0.0);
	boss_incoming_obj->AddUpdateComponent<BossIncomingUpdate>(main_scene_->GetLayerManager());
}

EnemyWaveBoss1::~EnemyWaveBoss1()
{
}

void EnemyWaveBoss1::OnDelete()
{
}

#include "EnemyWaveBoss2.h"

#include "EnemyWaveManager.h"
#include "MainScene.h"
#include "Boss2Mediator.h"
#include "BossIncomingUpdate.h"

EnemyWaveBoss2::EnemyWaveBoss2(MainScene* main_scene)
	:EnemyWaveBase(120,main_scene)
{
	auto obj = main_scene->AddObject(MatVec::Vector2(), 1.0, 0.0);
	obj->AddUpdateComponent<Boss2MediatorComponent>(main_scene->GetLayerManager(),main_scene->GetScoreManager(),main_scene->GetCollisionManager(),main_scene->GetEnemyWaveManager(), main_scene->mediator_);
	main_scene->GetEnemyWaveManager()->AddEnemyInWave(obj);
	auto boss_incoming_obj = main_scene->AddObject(MatVec::Vector2(), 1.0, 0.0);
	boss_incoming_obj->AddUpdateComponent<BossIncomingUpdate>(main_scene_->GetLayerManager());
}

EnemyWaveBoss2::~EnemyWaveBoss2()
{
}

void EnemyWaveBoss2::OnDelete()
{
}

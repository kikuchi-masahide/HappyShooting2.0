#include "EnemyWaveBoss1.h"

#include "EnemyWaveManager.h"
#include "MainScene.h"
#include "Boss1MediatorComponent.h"
#include "Boss1StateEntering.h"
#include "BossIncomingUpdate.h"
#include "EnemyWave6.h"

EnemyWaveBoss1::EnemyWaveBoss1(MainScene* main_scene)
	:EnemyWaveBase(180,main_scene)
{
	Log::OutputTrivial("start EnemyWaveBoss1;");
	auto boss = main_scene->AddObject(MatVec::Vector2(0, 900), 1.0, 0.0);
	auto mediator = boss->AddUpdateComponent<Boss1MediatorComponent>(
		main_scene->GetLayerManager(), main_scene->GetScoreManager(), main_scene->GetEnemyWaveManager(), main_scene->GetCollisionManager()
		);
	mediator->ChangeState(DBG_NEW Boss1StateEntering(mediator, main_scene->GetLayerManager(), main_scene->GetScoreManager(), main_scene->GetCollisionManager(), main_scene->GetEnemyWaveManager()));
	auto boss_incoming_obj = main_scene->AddObject(MatVec::Vector2(), 1.0, 0.0);
	boss_incoming_obj->AddUpdateComponent<BossIncomingUpdate>(main_scene_->GetLayerManager());
	main_scene_->GetEnemyWaveManager()->AddEnemyInWave(boss);
}

EnemyWaveBoss1::~EnemyWaveBoss1()
{
	Log::OutputTrivial("end EnemyWaveBoss1;");
}

void EnemyWaveBoss1::OnDelete()
{
	main_scene_->GetEnemyWaveManager()->SetWave(
		boost::shared_ptr<EnemyWave6>(new EnemyWave6(main_scene_))
	);
}

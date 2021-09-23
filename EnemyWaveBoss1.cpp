#include "stdafx.h"
#include "EnemyWaveBoss1.h"

#include "EnemyWaveManager.h"
#include "MainScene.h"
#include "Boss1MediatorComponent.h"
#include "Boss1StateEntering.h"

EnemyWaveBoss1::EnemyWaveBoss1(EnemyWaveManager* manager)
	:EnemyWaveBase(120,manager)
{
	auto scene = manager->scene_;
	auto boss = scene->AddObject(MatVec::Vector2(0, 900), 1.0, 0.0);
	auto mediator = boss->AddUpdateComponent<Boss1MediatorComponent>(
		scene->GetLayerManager(), scene->GetScoreManager(),scene->GetEnemyWaveManager(), scene->GetCollisionManager()
		);
	mediator->ChangeState(new Boss1StateEntering(mediator, scene->GetLayerManager(), scene->GetScoreManager(), scene->GetCollisionManager()));

}

EnemyWaveBoss1::~EnemyWaveBoss1()
{
}

void EnemyWaveBoss1::OnDelete()
{
}

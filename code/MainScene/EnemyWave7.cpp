#include "EnemyWave7.h"

#include "MainScene.h"
#include "Enemy7MediatorComponent.h"

EnemyWave7::EnemyWave7(MainScene* main_scene)
	:EnemyWaveBase(60, main_scene)
{
	auto obj = main_scene_->AddObject(MatVec::Vector2(), 1.0, 0.0);
	obj->AddUpdateComponent<Enemy7MediatorComponent>(main_scene->GetLayerManager(),main_scene->GetCollisionManager(), main_scene->GetScoreManager());
	main_scene->GetEnemyWaveManager()->AddEnemyInWave(obj);
}

EnemyWave7::~EnemyWave7()
{
}

void EnemyWave7::OnDelete()
{
}
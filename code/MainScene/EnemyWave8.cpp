#include "EnemyWave8.h"

#include "MainScene.h"
#include "Enemy8MediatorComponent.h"

EnemyWave8::EnemyWave8(MainScene* main_scene)
	:EnemyWaveBase(60,main_scene)
{
	for (int n = 0; n < 4; n++)
	{
		auto obj = main_scene_->AddObject(MatVec::Vector2(), 1.0, 0.0);
		obj->AddUpdateComponent<Enemy8MediatorComponent>(main_scene_->GetLayerManager(), main_scene_->GetCollisionManager(), main_scene_->GetScoreManager(), main_scene_->GetMyselfHandle());
		main_scene_->GetEnemyWaveManager()->AddEnemyInWave(obj);
	}
}

EnemyWave8::~EnemyWave8()
{
}

void EnemyWave8::OnDelete()
{
}

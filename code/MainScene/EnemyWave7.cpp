#include "EnemyWave7.h"

#include "MainScene.h"
#include "Enemy7MediatorComponent.h"
#include "EnemyWave8.h"

EnemyWave7::EnemyWave7(MainScene* main_scene)
	:EnemyWaveBase(60, main_scene)
{
	auto obj = main_scene_->AddObject(MatVec::Vector2(0.0, 900.0), 1.0, 0.0);
	obj->AddUpdateComponent<Enemy7MediatorComponent>(main_scene->GetLayerManager(),main_scene->GetCollisionManager(), main_scene->GetScoreManager());
	main_scene->GetEnemyWaveManager()->AddEnemyInWave(obj);
}

EnemyWave7::~EnemyWave7()
{
}

void EnemyWave7::OnDelete()
{
	main_scene_->GetEnemyWaveManager()->SetWave(boost::shared_ptr<EnemyWave8>(
		DBG_NEW EnemyWave8(main_scene_)
		));
}

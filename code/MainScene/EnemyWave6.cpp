#include "EnemyWave6.h"

#include "MainScene.h"
#include "Enemy6MediatorComponent.h"
#include "EnemyWave7.h"

EnemyWave6::EnemyWave6(MainScene* main_scene)
	:EnemyWaveBase(60,main_scene)
{
	//x移動量が正のもの
	auto obj_p = main_scene_->AddObject(MatVec::Vector2(startx_, starty_), 1.0, 0.0);
	obj_p->AddUpdateComponent<Enemy6MediatorComponent>(0, startx_, starty_, abs_dx_,
		Enemy6MediatorComponent::life0_,
		main_scene->GetLayerManager(), main_scene->GetScoreManager(),
		main_scene->GetEnemyWaveManager(), main_scene->GetCollisionManager());
	//x移動量が負のもの
	auto obj_m = main_scene_->AddObject(MatVec::Vector2(startx_, starty_), 1.0, 0.0);
	obj_m->AddUpdateComponent<Enemy6MediatorComponent>(0, startx_, starty_, -abs_dx_,
		Enemy6MediatorComponent::life0_,
		main_scene->GetLayerManager(), main_scene->GetScoreManager(),
		main_scene->GetEnemyWaveManager(), main_scene->GetCollisionManager());
}

EnemyWave6::~EnemyWave6()
{
	Log::OutputTrivial("end EnemyWave6");
}

void EnemyWave6::OnDelete()
{
	main_scene_->GetEnemyWaveManager()->SetWave(boost::shared_ptr<EnemyWave7>(
		new EnemyWave7(main_scene_)
		));
}

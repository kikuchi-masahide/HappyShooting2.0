#include "EnemyWave6.h"

#include "MainScene.h"
#include "Enemy6MediatorComponent.h"

EnemyWave6::EnemyWave6(MainScene* main_scene)
	:EnemyWaveBase(60,main_scene)
{
	//xˆÚ“®—Ê‚ª³‚Ì‚à‚Ì
	auto obj_p = main_scene_->AddObject(MatVec::Vector2(startx_, starty_), 1.0, 0.0);
	obj_p->AddUpdateComponent<Enemy6MediatorComponent>(0, startx_, starty_, abs_dx_,
		Enemy6MediatorComponent::life0_,
		main_scene->GetLayerManager(), main_scene->GetScoreManager(),
		main_scene->GetEnemyWaveManager(), main_scene->GetCollisionManager());
	//xˆÚ“®—Ê‚ª•‰‚Ì‚à‚Ì
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
}

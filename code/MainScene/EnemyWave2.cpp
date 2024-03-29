#include "EnemyWave2.h"

#include "EnemyWaveManager.h"
#include "MainScene.h"
#include "Enemy1MoveComponent.h"
#include "EnemyHealthComponent.h"
#include "Enemy1CollisionComponent.h"
#include "DrawTextureComponent.h"
#include "EnemyWave3.h"

EnemyWave2::EnemyWave2(unsigned int tick_after_clear, MainScene* main_scene)
	:EnemyWaveBase(tick_after_clear, main_scene)
{
	Log::OutputTrivial("start EnemyWave2;");
	auto enemyman = main_scene->GetEnemyWaveManager();
	for (unsigned int index = 0; index < all_number_; index++)
	{
		auto e1 = main_scene->AddObject(MatVec::Vector2(0, 450) - MatVec::Vector2(speedx_, speedy_) * (5 + period_ * index), 1.0, 0.0);
		e1->AddUpdateComponent<Enemy1MoveComponent>(0, MatVec::Vector2(speedx_, speedy_), angle_);
		auto health = e1->AddUpdateComponent<EnemyHealthComponent>(main_scene->GetLayerManager(), 100);
		e1->AddUpdateComponent<Enemy1CollisionComponent>(main_scene->GetCollisionManager(), main_scene->GetScoreManager(), health);
		auto texture = e1->AddOutputComponent<DrawTextureComponent>(main_scene->GetLayerManager(), 7, -5);
		texture->width_ = 40;
		texture->height_ = 40;
		enemyman->AddEnemyInWave(e1);
	}
}

EnemyWave2::~EnemyWave2()
{
	Log::OutputTrivial("end EnemyWave2;");
}

void EnemyWave2::OnDelete()
{
	main_scene_->GetEnemyWaveManager()->SetWave(boost::shared_ptr<EnemyWave3>(
		DBG_NEW EnemyWave3(main_scene_)
	));
}

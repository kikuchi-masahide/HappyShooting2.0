#include "EnemyWave1.h"

#include "EnemyWaveManager.h"
#include "MainScene.h"
#include "Enemy1MoveComponent.h"
#include "EnemyHealthComponent.h"
#include "Enemy1CollisionComponent.h"
#include "DrawTextureComponent.h"
#include "EnemyWave2.h"

EnemyWave1::EnemyWave1(unsigned int tick_after_clear, MainScene* main_scene)
	:EnemyWaveBase(tick_after_clear, main_scene)
{
	for (unsigned int index = 0; index < all_number_; index++)
	{
		auto e1 = main_scene->AddObject(MatVec::Vector2(0, 450) - MatVec::Vector2(speedx_, speedy_) * (5+period_*index), 1.0, 0.0);
		e1->AddUpdateComponent<Enemy1MoveComponent>(0, MatVec::Vector2(speedx_, speedy_), angle_);
		auto health = e1->AddUpdateComponent<EnemyHealthComponent>(main_scene->GetLayerManager(), 100);
		e1->AddUpdateComponent<Enemy1CollisionComponent>(main_scene->GetCollisionManager(), main_scene->GetScoreManager(), health);
		auto texture = e1->AddOutputComponent<DrawTextureComponent>(main_scene->GetLayerManager(), 7, -5);
		texture->width_ = 40;
		texture->height_ = 40;
		AddEnemy(e1);
	}
}

EnemyWave1::~EnemyWave1()
{
}

void EnemyWave1::OnDelete()
{
	main_scene_->GetEnemyWaveManager()->SetWave(boost::shared_ptr<EnemyWave2>(
		DBG_NEW EnemyWave2(30,main_scene_))
	);
}

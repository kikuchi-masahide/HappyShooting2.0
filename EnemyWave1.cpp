#include "stdafx.h"
#include "EnemyWave1.h"

#include "EnemyWaveManager.h"
#include "MainScene.h"
#include "Enemy1MoveComponent.h"
#include "EnemyHealthComponent.h"
#include "Enemy1CollisionComponent.h"
#include "DrawTextureComponent.h"
#include "EnemyWave2.h"

//TODO:Wave1‚ªˆê¶Ž€‚ÉØ‚ç‚È‚¢ ‚È‚º
EnemyWave1::EnemyWave1(unsigned int tick_after_clear, EnemyWaveManager* manager)
	:EnemyWaveBase(tick_after_clear,manager)
{
	MainScene* scene = manager->scene_;
	for (unsigned int index = 0; index < all_number_; index++)
	{
		auto e1 = scene->AddObject(MatVec::Vector2(0, 450) - MatVec::Vector2(speedx_, speedy_) * (5+period_*index), 1.0, 0.0);
		e1->AddUpdateComponent<Enemy1MoveComponent>(0, MatVec::Vector2(speedx_, speedy_), angle_);
		auto health = e1->AddUpdateComponent<EnemyHealthComponent>(scene->GetLayerManager(), 100);
		e1->AddUpdateComponent<Enemy1CollisionComponent>(scene->GetCollisionManager(), scene->GetScoreManager(), health);
		auto texture = e1->AddOutputComponent<DrawTextureComponent>(scene->GetLayerManager(), 7, -5);
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
	manager_->SetWave(boost::shared_ptr<EnemyWave2>(
		new EnemyWave2(30,manager_))
	);
}

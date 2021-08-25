#include "stdafx.h"
#include "EnemyWave45.h"

#include "EnemyWaveManager.h"
#include "MainScene.h"
#include "Enemy5MoveComponent.h"
#include "DrawTextureComponent.h"
#include "EnemyHealthComponent.h"
#include "Enemy3CollisionComponent.h"
#include "DrawHealthBarComponent.h"
#include "Enemy5ShootComponent.h"

EnemyWave45::EnemyWave45(EnemyWaveManager* manager)
	:EnemyWaveBase(120,manager)
{
	auto scene = manager_->scene_;
	for (int i = 0; i < 8; i++)
	{
		auto obj = scene->AddObject(MatVec::Vector2(), 1.0, 0.0);
		obj->AddUpdateComponent<Enemy5MoveComponent>(-30 * i);
		auto draw = obj->AddOutputComponent<DrawTextureComponent>(scene->GetLayerManager(), 8, -5);
		draw->width_ = 40;
		draw->height_ = 40;
		auto health = obj->AddUpdateComponent<EnemyHealthComponent>(scene->GetLayerManager(), 300);
		//Enemy3‚ÆŒ`‚ªˆê‚È‚Ì‚Å“–‚½‚è”»’è‚àˆê
		obj->AddUpdateComponent<Enemy3CollisionComponent>(scene->GetCollisionManager(), scene->GetScoreManager(), health);
		obj->AddOutputComponent<DrawHealthBarComponent>(scene->GetLayerManager(), health, MatVec::Vector2(0, 30));
		obj->AddUpdateComponent<Enemy5ShootComponent>(50, scene->GetMyselfHandle(), 10, 4, 60, 0, 100, scene->GetLayerManager(), scene->GetCollisionManager());
		AddEnemy(obj);
	}
}

EnemyWave45::~EnemyWave45()
{
}

void EnemyWave45::OnDelete()
{
	manager_->SetWave(nullptr);
}

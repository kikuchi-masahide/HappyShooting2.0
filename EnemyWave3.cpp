#include "stdafx.h"
#include "EnemyWave3.h"

#include "EnemyWaveManager.h"
#include "MainScene.h"
#include "Enemy3MoveComponent.h"
#include "DrawTextureComponent.h"
#include "EnemyHealthComponent.h"
#include "Enemy3CollisionComponent.h"
#include "NormalShootComponent.h"

EnemyWave3::EnemyWave3(EnemyWaveManager* manager)
	:EnemyWaveBase(60,manager)
{
	auto lambda = [](double angle)
	{
		return MatVec::Vector2(300 * cos(angle) - 300, -450 * sin(angle) + 490);
	};
	auto scene = manager->scene_;
	for (int i = 0; i < 9; i++)
	{
		auto obj = scene->AddObject(MatVec::Vector2(), 0.0, 1.0);
		obj->AddUpdateComponent<Enemy3MoveComponent>(-i * 30, lambda,PI/600);
		auto draw = obj->AddOutputComponent<DrawTextureComponent>(scene->GetLayerManager(), 8, -10);
		draw->width_ = 40;
		draw->height_ = 40;
		auto health = obj->AddUpdateComponent<EnemyHealthComponent>(scene->GetLayerManager(), 300);
		obj->AddUpdateComponent<Enemy3CollisionComponent>(scene->GetCollisionManager(), scene->GetScoreManager(), health);
		for (int d = 0; d < 4; d++)
		{
			MatVec::Vector2 direct(cos(d * PI / 2), sin(d * PI / 2));
			direct *= bullet_speed_;
			obj->AddUpdateComponent<NormalShootComponent>(
				50, direct, bullet_size_, 60, bullet_attack_, scene->GetLayerManager(), scene->GetCollisionManager()
				);
		}
	}
	auto lambda2 = [](double angle)
	{
		return MatVec::Vector2(-300 * cos(angle) + 300, -450 * sin(angle) + 490);
	};
	for (int i = 0; i < 9; i++)
	{
		auto obj = scene->AddObject(MatVec::Vector2(), 0.0, 1.0);
		obj->AddUpdateComponent<Enemy3MoveComponent>(-i * 30, lambda2, PI / 600);
		auto draw = obj->AddOutputComponent<DrawTextureComponent>(scene->GetLayerManager(), 8, -10);
		draw->width_ = 40;
		draw->height_ = 40;
		auto health = obj->AddUpdateComponent<EnemyHealthComponent>(scene->GetLayerManager(), 300);
		obj->AddUpdateComponent<Enemy3CollisionComponent>(scene->GetCollisionManager(), scene->GetScoreManager(), health);
		for (int d = 0; d < 4; d++)
		{
			MatVec::Vector2 direct(cos(d * PI / 2), sin(d * PI / 2));
			direct *= bullet_speed_;
			obj->AddUpdateComponent<NormalShootComponent>(
				50, direct, bullet_size_, 60, bullet_attack_, scene->GetLayerManager(), scene->GetCollisionManager()
				);
		}
	}
}

EnemyWave3::~EnemyWave3()
{
}

void EnemyWave3::OnDelete()
{
	manager_->SetWave(nullptr);
}

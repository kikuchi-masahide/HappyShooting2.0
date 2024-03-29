#include "EnemyWave3.h"

#include "EnemyWaveManager.h"
#include "MainScene.h"
#include "Enemy3MoveComponent.h"
#include "DrawTextureComponent.h"
#include "EnemyHealthComponent.h"
#include "Enemy3CollisionComponent.h"
#include "NormalShootComponent.h"
#include "DrawHealthBarComponent.h"
#include "EnemyWave45.h"

EnemyWave3::EnemyWave3(MainScene* main_scene)
	:EnemyWaveBase(60,main_scene)
{
	Log::OutputTrivial("start EnemyWave3;");
	auto lambda = [](double angle)
	{
		return MatVec::Vector2(300 * cos(angle) - 300, -450 * sin(angle) + 490);
	};
	auto enemywaveman = main_scene->GetEnemyWaveManager();
	for (int i = 0; i < 9; i++)
	{
		auto obj = main_scene->AddObject(MatVec::Vector2(0.0,900.0), 0.0, 1.0);
		obj->AddUpdateComponent<Enemy3MoveComponent>(-i * 30, lambda,PI/600);
		auto draw = obj->AddOutputComponent<DrawTextureComponent>(main_scene->GetLayerManager(), 8, -5);
		draw->width_ = 40;
		draw->height_ = 40;
		auto health = obj->AddUpdateComponent<EnemyHealthComponent>(main_scene->GetLayerManager(), 300);
		obj->AddUpdateComponent<Enemy3CollisionComponent>(main_scene->GetCollisionManager(), main_scene->GetScoreManager(), health);
		obj->AddOutputComponent<DrawHealthBarComponent<EnemyHealthComponent>>(main_scene->GetLayerManager(), health, MatVec::Vector2(0, 30));
		for (int d = 0; d < 4; d++)
		{
			MatVec::Vector2 direct(cos(d * PI / 2), sin(d * PI / 2));
			direct *= bullet_speed_;
			obj->AddUpdateComponent<NormalShootComponent>(
				50, direct, bullet_size_, 60, bullet_attack_, main_scene->GetLayerManager(), main_scene->GetCollisionManager()
				);
		}
		enemywaveman->AddEnemyInWave(obj);
	}
	auto lambda2 = [](double angle)
	{
		return MatVec::Vector2(-300 * cos(angle) + 300, -450 * sin(angle) + 490);
	};
	for (int i = 0; i < 9; i++)
	{
		auto obj = main_scene->AddObject(MatVec::Vector2(0.0, 900.0), 0.0, 1.0);
		obj->AddUpdateComponent<Enemy3MoveComponent>(-i * 30, lambda2, PI / 600);
		auto draw = obj->AddOutputComponent<DrawTextureComponent>(main_scene->GetLayerManager(), 8, -5);
		draw->width_ = 40;
		draw->height_ = 40;
		auto health = obj->AddUpdateComponent<EnemyHealthComponent>(main_scene->GetLayerManager(), 300);
		obj->AddUpdateComponent<Enemy3CollisionComponent>(main_scene->GetCollisionManager(), main_scene->GetScoreManager(), health);
		obj->AddOutputComponent<DrawHealthBarComponent<EnemyHealthComponent>>(main_scene->GetLayerManager(), health, MatVec::Vector2(0, 30));
		for (int d = 0; d < 4; d++)
		{
			MatVec::Vector2 direct(cos(d * PI / 2), sin(d * PI / 2));
			direct *= bullet_speed_;
			obj->AddUpdateComponent<NormalShootComponent>(
				50, direct, bullet_size_, 60, bullet_attack_, main_scene->GetLayerManager(), main_scene->GetCollisionManager()
				);
		}
		enemywaveman->AddEnemyInWave(obj);
	}
}

EnemyWave3::~EnemyWave3()
{
	Log::OutputTrivial("emd EnemyWave3;");
}

void EnemyWave3::OnDelete()
{
	main_scene_->GetEnemyWaveManager()->SetWave(boost::shared_ptr<EnemyWave45>(
		DBG_NEW EnemyWave45(main_scene_)
		));
}

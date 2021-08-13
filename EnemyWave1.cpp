#include "stdafx.h"
#include "EnemyWave1.h"

#include "EnemyWaveManager.h"
#include "MainScene.h"
#include "LinearMoveComponent.h"
#include "LinearRotateComponent.h"
#include "EnemyHealthComponent.h"
#include "Enemy1CollisionComponent.h"
#include "DrawTextureComponent.h"

EnemyWave1::EnemyWave1(unsigned int tick_after_clear, EnemyWaveManager* manager)
	:EnemyWaveBase(tick_after_clear,manager)
{
	MainScene* scene = manager->scene_;
	double dist = sqrt(
		300 * 300 + 450 * 450
	);
	double speedx = -dist * 2 / 600;
	double speedy = -dist * 3 / 600;
	auto e1 = scene->AddObject(MatVec::Vector2(0, 450) - MatVec::Vector2(speedx, speedy) * 5, 1.0, 0.0);
	e1->AddUpdateComponent<LinearMoveComponent>(MatVec::Vector2(speedx, speedy), dist / 120 * 5);
	e1->AddUpdateComponent<LinearRotateComponent>(PI / 60);
	auto health = e1->AddUpdateComponent<EnemyHealthComponent>(scene, 100);
	e1->AddUpdateComponent<Enemy1CollisionComponent>(scene, health);
	auto texture = e1->AddOutputComponent<DrawTextureComponent>(scene->GetLayerManager(), 7);
	texture->width_ = 40;
	texture->height_ = 40;
	AddEnemy(e1);
}

EnemyWave1::~EnemyWave1()
{
}

void EnemyWave1::OnDelete()
{
	manager_->SetWave(nullptr);
}

#include "stdafx.h"
#include "Enemy3CollisionComponent.h"

#include "GameObject.h"
#include "Math.h"
#include "EnemyHealthComponent.h"
#include "ScoreManager.h"

Enemy3CollisionComponent::Enemy3CollisionComponent(GameObjectHandle object, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<ScoreManager> score_manager, ComponentHandle<EnemyHealthComponent> health)
	:EnemyBodyCollisionComponent(object, collision_manager, score_manager, health, damage_, 100),
	circle_(This<CollisionComponent>(),MatVec::Vector2(),20)
{
}

Enemy3CollisionComponent::~Enemy3CollisionComponent()
{
}

void Enemy3CollisionComponent::Update()
{
	MatVec::Vector2 center = mObj->GetPosition();
	circle_.center_ = center;
	manager_->AddGeometry(&circle_);
}

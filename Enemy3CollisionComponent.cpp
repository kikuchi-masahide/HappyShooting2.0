#include "stdafx.h"
#include "Enemy3CollisionComponent.h"

#include "GameObject.h"
#include "Math.h"
#include "EnemyHealthComponent.h"
#include "ScoreManager.h"

Enemy3CollisionComponent::Enemy3CollisionComponent(GameObjectHandle object, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<ScoreManager> score_manager, ComponentHandle<EnemyHealthComponent> health)
	:CollisionComponent(object, collision_manager, 100, CollisionManager::Tag::EnemyBody, damage_),
	health_component_(health), score_manager_(score_manager),
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

void Enemy3CollisionComponent::CheckHitComponent()
{
	for (auto comp : hit_comps_)
	{
		if (comp->tag_ == CollisionManager::Tag::Myself || comp->tag_ == CollisionManager::Tag::MyBullet)
		{
			auto damage = comp->GetDamage();
			auto real_damage = health_component_->Damage(damage);
			score_manager_->AddScore(real_damage);
		}
	}
}

#include "stdafx.h"
#include "Enemy1CollisionComponent.h"

#include "EnemyHealthComponent.h"

Enemy1CollisionComponent::Enemy1CollisionComponent(GameObjectHandle object, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<ScoreManager> score_manager, ComponentHandle<EnemyHealthComponent> health)
	:CollisionComponent(object, collision_manager, 100, CollisionManager::Tag::EnemyBody, damage_),
	health_component_(health), score_manager_(score_manager)
{
	circle_around_[0].radius_ = 8;
	circle_around_[1].radius_ = 8;
	circle_around_[2].radius_ = 8;
	circle_center_.radius_ = 4;
}

Enemy1CollisionComponent::~Enemy1CollisionComponent()
{
}

void Enemy1CollisionComponent::Update()
{
	MatVec::Vector2 center = mObj->GetPosition();
	double angle = mObj->GetRotation();
	double dist = (double)(2 * 8) / sqrt(3);
	for (unsigned int n = 0; n < 3; n++)
	{
		CircleGeometry circle(
			This<CollisionComponent>(), MatVec::Vector2(center(0) + dist * cos(angle), center(1) + dist * sin(angle)), 8
		);
		manager_->AddCircleGeometry(circle);
		angle += 2 * PI / 3;
	}
	CircleGeometry circle(
		This<CollisionComponent>(), center, 4
	);
	manager_->AddCircleGeometry(circle);
}

void Enemy1CollisionComponent::CheckHitComponent()
{
	for (auto comp : hit_comps_)
	{
		//Ž©‹@‚Ü‚½‚ÍŽ©‹@’e‚Æ‚ÌÕ“Ë
		if (comp->tag_ == CollisionManager::Tag::Myself || comp->tag_ == CollisionManager::Tag::MyBullet)
		{
			auto damage = comp->GetDamage();
			auto real_damage = health_component_->Damage(damage);
			score_manager_->AddScore(real_damage);
		}
	}
}


#include "stdafx.h"
#include "Enemy1CollisionComponent.h"

#include "EnemyHealthComponent.h"

Enemy1CollisionComponent::Enemy1CollisionComponent(MainScene* scene, GameObjectHandle object, ComponentHandle<EnemyHealthComponent> health)
	:CollisionComponent(100,2,damage_),scene_(scene),object_(object),health_component_(health)
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
	for (auto comp : hit_comps_)
	{
		//Ž©‹@‚Ü‚½‚ÍŽ©‹@’e‚Æ‚ÌÕ“Ë
		if (comp->tag_ == 0 || comp->tag_ == 1)
		{
			auto damage = comp->GetDamage();
			health_component_->Damage(damage);
			scene_->AddScore(damage);
		}
	}
	hit_comps_.clear();
	scene_->collision_manager_.AddCollisionComponent(This<CollisionComponent>());
}

void Enemy1CollisionComponent::AddGeometryToManager(CollisionManager& manager)
{
	MatVec::Vector2 center = object_->GetPosition();
	double angle = object_->GetRotation();
	double dist = (double)(2 * 8) / sqrt(3);
	for (unsigned int n = 0; n < 3; n++)
	{
		manager.circles_.push_back(CircleGeometry(
			This<CollisionComponent>(), MatVec::Vector2(center(0) + dist * cos(angle), center(1) + dist * sin(angle)), 8
		));
		angle += 2 * PI / 3;
	}
	manager.circles_.push_back(CircleGeometry(
		This<CollisionComponent>(), center, 4
	));
}


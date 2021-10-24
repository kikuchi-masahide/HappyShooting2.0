#include "stdafx.h"
#include "Enemy1CollisionComponent.h"

#include "EnemyHealthComponent.h"

Enemy1CollisionComponent::Enemy1CollisionComponent(GameObjectHandle object, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<ScoreManager> score_manager, ComponentHandle<EnemyHealthComponent> health)
	:EnemyBodyCollisionComponent(object, collision_manager, score_manager, health, damage_, 100)
{
	circle_around_[0] = CircleGeometry(This<CollisionComponent>(), MatVec::Vector2(), 8);
	circle_around_[1] = CircleGeometry(This<CollisionComponent>(), MatVec::Vector2(), 8);
	circle_around_[2] = CircleGeometry(This<CollisionComponent>(), MatVec::Vector2(), 8);
	circle_center_ = CircleGeometry(This<CollisionComponent>(), MatVec::Vector2(), 4);
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
		circle_around_[n].center_ = MatVec::Vector2(center(0) + dist * cos(angle), center(1) + dist * sin(angle));
		manager_->AddGeometry(&(circle_around_[n]));
		angle += 2 * PI / 3;
	}
	CircleGeometry circle(
		This<CollisionComponent>(), center, 4
	);
	manager_->AddGeometry(&circle_center_);
}
#include "Enemy7CollisionComponent.h"

Enemy7CollisionComponent::Enemy7CollisionComponent(GameObjectHandle object, boost::shared_ptr<CollisionManager> col, boost::shared_ptr<ScoreManager> score, ComponentHandle<EnemyHealthComponent> health)
	:EnemyBodyCollisionComponent(object,col,score,health,100)
{
	circle_ = CircleGeometry(This<CollisionComponent>(),MatVec::Vector2(), 20);
	auto deg = mObj->GetRotation();
	circle_small_[0] = CircleGeometry(This<CollisionComponent>(), MatVec::Vector2(), 4);
	circle_small_[1] = CircleGeometry(This<CollisionComponent>(), MatVec::Vector2(), 4);
}

Enemy7CollisionComponent::~Enemy7CollisionComponent()
{
}

void Enemy7CollisionComponent::Update()
{
	auto center = mObj->GetPosition();
	auto deg = mObj->GetRotation();
	circle_.center_ = center;
	circle_small_[0].center_ = center + MatVec::Vector2(cos(deg), sin(deg)) * 20;
	circle_small_[1].center_ = center - MatVec::Vector2(cos(deg), sin(deg)) * 20;
	manager_->AddEnemyGeometry(&circle_);
	manager_->AddEnemyGeometry(&(circle_small_[0]));
	manager_->AddEnemyGeometry(&(circle_small_[1]));
}

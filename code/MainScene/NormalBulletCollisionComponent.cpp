#include "NormalBulletCollisionComponent.h"

#include "../Engine/GameObject.h"

NormalBulletCollisionComponent::NormalBulletCollisionComponent(GameObjectHandle obj, double radius, unsigned int damage, boost::shared_ptr<CollisionManager> collision_manager)
	:CollisionComponent(obj,collision_manager,50,CollisionManager::Tag::EnemyBullet,damage)
{
	circle_ = CircleGeometry(This<CollisionComponent>(), mObj->GetPosition(), radius);
}

NormalBulletCollisionComponent::~NormalBulletCollisionComponent()
{
}

void NormalBulletCollisionComponent::Update()
{
	circle_.center_ = mObj->GetPosition();
	manager_->AddEnemyGeometry(&circle_);
}

void NormalBulletCollisionComponent::CheckHitComponent()
{
	//この弾が自機と当たった場合の削除処理等はあちらでやるので，ここでやることは何もない
}

#include "stdafx.h"
#include "NormalBulletCollisionComponent.h"

#include "code/Engine/GameObject.h"

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
	//���̒e�����@�Ɠ��������ꍇ�̍폜�������͂�����ł��̂ŁC�����ł�邱�Ƃ͉����Ȃ�
}

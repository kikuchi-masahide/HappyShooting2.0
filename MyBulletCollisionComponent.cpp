#include "stdafx.h"
#include "MyBulletCollisionComponent.h"

#include "CircleGeometry.h"
#include "MainScene.h"

MyBulletCollisionComponent::MyBulletCollisionComponent(GameObjectHandle obj, boost::shared_ptr<CollisionManager> manager, unsigned int damage, double radius)
	:CollisionComponent(obj, manager, 50, CollisionManager::Tag::MyBullet,damage),
	radius_(radius)
{
	circle_ = CircleGeometry(This<CollisionComponent>(), mObj->GetPosition(), radius_);
}

MyBulletCollisionComponent::~MyBulletCollisionComponent()
{
}

void MyBulletCollisionComponent::Update()
{
	circle_.center_ = mObj->GetPosition();
	manager_->AddGeometry(&circle_);
}

void MyBulletCollisionComponent::CheckHitComponent()
{
	for (auto comp : hit_comps_)
	{
		if (comp->tag_ == CollisionManager::Tag::EnemyBody)
		{
			SetDeleteFlag();
			mObj->SetDeleteFlag();
			break;
		}
	}
}


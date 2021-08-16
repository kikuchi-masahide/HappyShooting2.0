#include "stdafx.h"
#include "MyBulletCollisionComponent.h"

#include "CircleGeometry.h"
#include "MainScene.h"

MyBulletCollisionComponent::MyBulletCollisionComponent(GameObjectHandle obj, boost::shared_ptr<CollisionManager> manager, unsigned int damage, double radius)
	:CollisionComponent(obj, manager, 50, 1,damage),
	radius_(radius)
{
}

MyBulletCollisionComponent::~MyBulletCollisionComponent()
{
}

void MyBulletCollisionComponent::Update()
{
	CircleGeometry circle(This<CollisionComponent>(), mObj->GetPosition(), radius_);
	manager_->AddCircleGeometry(circle);
}

void MyBulletCollisionComponent::CheckHitComponent()
{
	for (auto comp : hit_comps_)
	{
		if (comp->tag_ == 2)
		{
			SetDeleteFlag();
			mObj->SetDeleteFlag();
			break;
		}
	}
}


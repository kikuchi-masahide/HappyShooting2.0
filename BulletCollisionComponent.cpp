#include "stdafx.h"
#include "BulletCollisionComponent.h"

#include "CircleGeometry.h"
#include "MainScene.h"

BulletCollisionComponent::BulletCollisionComponent(GameObjectHandle obj, boost::shared_ptr<CollisionManager> manager, int upd_priority, unsigned int mytag, unsigned int enemytag, unsigned int damage, double radius, bool double_suicide)
	:CollisionComponent(obj, manager, upd_priority,mytag,damage),
	enemy_tag_(enemytag),radius_(radius),double_suicide_(double_suicide)
{
}

BulletCollisionComponent::~BulletCollisionComponent()
{
}

void BulletCollisionComponent::Update()
{
	CircleGeometry circle(This<CollisionComponent>(), mObj->GetPosition(), radius_);
	manager_->AddCircleGeometry(circle);
}

void BulletCollisionComponent::CheckHitComponent()
{
	for (auto comp : hit_comps_)
	{
		if (comp->tag_ == enemy_tag_)
		{
			SetDeleteFlag();
			if (double_suicide_)
			{
				mObj->SetDeleteFlag();
			}
			break;
		}
	}
}


#include "stdafx.h"
#include "BulletCollisionComponent.h"

#include "CircleGeometry.h"
#include "MainScene.h"

BulletCollisionComponent::BulletCollisionComponent(MainScene* scene, GameObjectHandle obj, int upd_priority, unsigned int mytag, unsigned int enemytag, unsigned int damage, double radius, bool double_suicide)
	:CollisionComponent(upd_priority,mytag,damage),
	enemy_tag_(enemytag),radius_(radius),double_suicide_(double_suicide),scene_(scene),obj_(obj)
{
}

BulletCollisionComponent::~BulletCollisionComponent()
{
}

void BulletCollisionComponent::Update()
{
	CircleGeometry circle(This<CollisionComponent>(), obj_->GetPosition(), radius_);
	scene_->collision_manager_.AddCircleGeometry(circle);
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
				obj_->SetDeleteFlag();
			}
			break;
		}
	}
}


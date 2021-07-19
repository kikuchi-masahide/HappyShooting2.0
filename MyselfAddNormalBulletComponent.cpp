#include "stdafx.h"
#include "MyselfAddNormalBulletComponent.h"

#include "GameObject.h"
#include "MainScene.h"
#include "LinearMoveComponent.h"
#include "DrawNormalBulletComponent.h"
#include "BulletCollisionComponent.h"

MyselfAddNormalBulletComponent::MyselfAddNormalBulletComponent(GameObjectHandle handle, MainScene* scene)
	:Component(handle, 30),
	time_(0),scene_(scene)
{
}

MyselfAddNormalBulletComponent::~MyselfAddNormalBulletComponent()
{
}

void MyselfAddNormalBulletComponent::Update()
{
	if (time_ == period_to_fire_)
	{
		double angle = mObj->GetRotation();
		auto pos = mObj->GetPosition();
		GameObjectHandle bullet = scene_->AddObject(pos, 1.0, angle);
		auto dist = MatVec::Vector2(cos(angle) * moving_dist_, sin(angle) * moving_dist_);
		bullet->AddUpdateComponent<LinearMoveComponent>(
			dist, bullet_redius_
		);
		bullet->AddUpdateComponent<BulletCollisionComponent>(scene_, 50, 1, 2, 100, bullet_redius_);
		bullet->AddOutputComponent<DrawNormalBulletComponent>(
			scene_->GetLayerManager(), bullet_redius_, MatVec::Vector3(0.0, 0.0, 1.0), 1.0
		);
		time_ = 0;
	}
	time_++;
}


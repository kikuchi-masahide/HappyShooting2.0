#include "stdafx.h"
#include "MyselfAddNormalBulletComponent.h"

#include "GameObject.h"
#include "MainScene.h"
#include "LinearMoveComponent.h"
#include "DrawNormalBulletComponent.h"

MyselfAddNormalBulletComponent::MyselfAddNormalBulletComponent(GameObjectHandle handle, MainScene* scene)
	:Component(30),
	object_(handle), time_(0),scene_(scene)
{
}

MyselfAddNormalBulletComponent::~MyselfAddNormalBulletComponent()
{
}

void MyselfAddNormalBulletComponent::Update()
{
	if (time_ == period_to_fire_)
	{
		double angle = object_->GetRotation();
		auto pos = object_->GetPosition();
		GameObjectHandle bullet = scene_->AddObject(pos, 1.0, angle);
		auto dist = MatVec::Vector2(cos(angle) * moving_dist_, sin(angle) * moving_dist_);
		bullet->AddUpdateComponent<LinearMoveComponent>(
			bullet, dist, bullet_redius_
		);
		bullet->AddOutputComponent<DrawNormalBulletComponent>(
			scene_, bullet, bullet_redius_, MatVec::Vector3(0.0, 0.0, 1.0), 1.0
		);
		time_ = 0;
	}
	time_++;
}


#include "stdafx.h"
#include "Enemy5ShootComponent.h"

#include "code/Engine/GameObject.h"
#include "code/Engine/Scene.h"
#include "LinearMoveComponent.h"
#include "DrawNormalBulletComponent.h"
#include "NormalBulletCollisionComponent.h"

Enemy5ShootComponent::Enemy5ShootComponent(GameObjectHandle handle, int priority, GameObjectHandle myself, double radius, double speed, unsigned int period, int counter0, unsigned int attack, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<CollisionManager> collision_manager, MatVec::Vector3 edge_rgb, double edge_alpha)
	:Component(handle,priority),
	myself_(myself),attack_(attack),period_(period),counter_(counter0),radius_(radius),speed_(speed),
	layer_manager_(layer_manager),collision_manager_(collision_manager),edge_rgb_(edge_rgb),
	edge_alpha_(edge_alpha)
{
}

Enemy5ShootComponent::~Enemy5ShootComponent()
{
}

void Enemy5ShootComponent::Update()
{
	if (counter_ == 0)
	{
		MatVec::Vector2 direct = myself_->GetPosition() - mObj->GetPosition();
		direct *= speed_ / direct.Norm();
		auto obj = mObj->mScene->AddObject(mObj->GetPosition(), 1.0, 0.0);
		obj->AddUpdateComponent<LinearMoveComponent>(direct, radius_);
		obj->AddOutputComponent<DrawNormalBulletComponent>(layer_manager_, radius_, edge_rgb_, edge_alpha_, -10.0);
		obj->AddUpdateComponent<NormalBulletCollisionComponent>(radius_, attack_, collision_manager_);
	}
	counter_++;
	if (counter_ == period_)
	{
		counter_ = 0;
	}
}

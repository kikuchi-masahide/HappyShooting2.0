#include "MyselfAddNormalBulletComponent.h"

#include "../Engine/Game.h"
#include "../Engine/Scene.h"
#include "LinearMoveComponent.h"
#include "DrawNormalBulletComponent.h"
#include "MyBulletCollisionComponent.h"

MyselfAddNormalBulletComponent::MyselfAddNormalBulletComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<CollisionManager> collision_manager)
	:Component(handle, 30),
	time_(0),layer_manager_(layer_manager),collision_manager_(collision_manager)
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
		GameObjectHandle bullet = mObj->mScene->AddObject(pos, 1.0, angle);
		auto dist = MatVec::Vector2(cos(angle) * moving_dist_, sin(angle) * moving_dist_);
		bullet->AddUpdateComponent<LinearMoveComponent>(
			dist, bullet_redius_
		);
		bullet->AddUpdateComponent<MyBulletCollisionComponent>(collision_manager_, 100, bullet_redius_);
		bullet->AddOutputComponent<DrawNormalBulletComponent>(
			layer_manager_, bullet_redius_, MatVec::Vector3(0.0, 0.0, 1.0), 1.0, 10.0
		);
		time_ = 0;
	}
	time_++;
}

#include "NormalShootComponent.h"

#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "LinearMoveComponent.h"
#include "DrawNormalBulletComponent.h"
#include "NormalBulletCollisionComponent.h"

NormalShootComponent::NormalShootComponent(GameObjectHandle handle, int priority, MatVec::Vector2 direction, double radius, unsigned int period, unsigned int attack, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<CollisionManager> collision_manager, MatVec::Vector3 edge_rgb, double edge_alpha)
	:Component(handle, priority),
	direction_(direction),period_(period),attack_(attack),counter_(0),radius_(radius),
	layer_manager_(layer_manager),edge_rgb_(edge_rgb),edge_alpha_(edge_alpha),
	collision_manager_(collision_manager)
{
}

NormalShootComponent::~NormalShootComponent()
{
}

void NormalShootComponent::Update()
{
	if (counter_ == period_)
	{
		auto scene = mObj->mScene;
		auto obj = scene->AddObject(mObj->GetPosition(), 1.0, 0.0);
		obj->AddUpdateComponent<LinearMoveComponent>(direction_, radius_);
		obj->AddOutputComponent<DrawNormalBulletComponent>(layer_manager_, radius_, edge_rgb_, edge_alpha_, -10.0);
		obj->AddUpdateComponent<NormalBulletCollisionComponent>(radius_, attack_, collision_manager_);
		counter_ = 0;
	}
	counter_++;
}

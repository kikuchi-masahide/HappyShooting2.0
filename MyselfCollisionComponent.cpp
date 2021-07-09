#include "stdafx.h"
#include "MyselfCollisionComponent.h"

#include "MyselfMediatorComponent.h"
#include "GameObject.h"

#include "MainScene.h"

MyselfCollisionComponent::MyselfCollisionComponent(MainScene* scene, GameObjectHandle myself, ComponentHandle<MyselfMediatorComponent> mediator)
	:CollisionComponent(75,myself_tag_,damage_),
	/*collision_manager_(collision_manager)*/scene_(scene),geometry_(This<CollisionComponent>(),
	myself->GetPosition(),circle_radius_),myself_(myself),mediator_(mediator)
{
}

MyselfCollisionComponent::~MyselfCollisionComponent()
{
}

void MyselfCollisionComponent::Update()
{
	//円の位置更新
	geometry_.center_ = myself_->GetPosition();
	scene_->collision_manager_.circles_.push_back(geometry_);
}

void MyselfCollisionComponent::CheckHitComponent()
{
	//一発でも当たっていたらダメージを喰らう
	if (hit_comps_.size() > 0)
	{
		auto itr = hit_comps_.begin();
		mediator_->CauseDamageToMyself((*itr)->GetDamage());
	}
}

#include "MyselfCollisionComponent.h"

#include "MyselfMediatorComponent.h"
#include "../Engine/GameObject.h"

#include "MainScene.h"

MyselfCollisionComponent::MyselfCollisionComponent(GameObjectHandle myself, boost::shared_ptr<CollisionManager> manager, ComponentHandle<MyselfMediatorComponent> mediator)
	:CollisionComponent(myself, manager, 75,CollisionManager::Tag::Myself,damage_),
	geometry_(This<CollisionComponent>(), myself->GetPosition(),circle_radius_),mediator_(mediator)
{
}

MyselfCollisionComponent::~MyselfCollisionComponent()
{
}

void MyselfCollisionComponent::Update()
{
	//‰~‚ÌˆÊ’uXV
	geometry_.center_ = mObj->GetPosition();
	manager_->AddFriendlyGeometry(&geometry_);
}

void MyselfCollisionComponent::CheckHitComponent()
{
	mediator_->CheckHitComponent(hit_comps_);
}

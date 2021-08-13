#include "stdafx.h"
#include "MyselfCollisionComponent.h"

#include "MyselfMediatorComponent.h"
#include "GameObject.h"

#include "MainScene.h"

MyselfCollisionComponent::MyselfCollisionComponent(GameObjectHandle myself, boost::shared_ptr<CollisionManager> manager, ComponentHandle<MyselfMediatorComponent> mediator)
	:CollisionComponent(myself, manager, 75,myself_tag_,damage_),
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
	manager_->AddCircleGeometry(geometry_);
}

void MyselfCollisionComponent::CheckHitComponent()
{
	//“G’eC“G‹@‚ªˆê”­‚Å‚à“–‚½‚Á‚Ä‚¢‚½‚çƒ_ƒ[ƒW‚ð‹ò‚ç‚¤
	for (auto comp : hit_comps_)
	{
		if (comp->tag_ == 2)
		{
			mediator_->CauseDamageToMyself(comp->GetDamage());
			break;
		}
	}
}

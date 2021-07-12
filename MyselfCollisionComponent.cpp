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
	//‰~‚ÌˆÊ’uXV
	geometry_.center_ = myself_->GetPosition();
	scene_->collision_manager_.AddCircleGeometry(geometry_);
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

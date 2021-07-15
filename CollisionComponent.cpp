#include "stdafx.h"
#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(GameObjectHandle handle, int upd_priority, unsigned int tag, unsigned int damage)
	:Component(handle, upd_priority),
	tag_(tag),damage_(damage)
{
}

CollisionComponent::~CollisionComponent()
{
}

unsigned int CollisionComponent::GetDamage()
{
	return damage_;
}

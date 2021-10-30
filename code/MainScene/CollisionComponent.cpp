#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(GameObjectHandle handle, boost::shared_ptr<CollisionManager> manager, int upd_priority, CollisionManager::Tag tag, unsigned int damage)
	:Component(handle, upd_priority),
	tag_(tag),damage_(damage),manager_(manager)
{
}

CollisionComponent::~CollisionComponent()
{
}

unsigned int CollisionComponent::GetDamage()
{
	return damage_;
}

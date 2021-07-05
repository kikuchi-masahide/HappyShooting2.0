#include "stdafx.h"
#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::AddCollisionComponent(ComponentHandle<CollisionComponent> collision_comp)
{
	collision_comps_.push_back(collision_comp);
}

void CollisionManager::TraverseAll()
{
	collision_comps_.clear();
}

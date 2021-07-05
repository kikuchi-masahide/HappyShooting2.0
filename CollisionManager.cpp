#include "stdafx.h"
#include "CollisionManager.h"

#include "CollisionComponent.h"

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
	//ô½ÀWÌÇÁ
	for (auto& comp : collision_comps_)
	{
		comp->AddGeometryToManager(*this);
	}
	
	//AABBÌ¶xÀW¸ÅÀÑÖ¦
	std::sort(circles_.begin(), circles_.end(), [](const CircleGeometry& left, const CircleGeometry& right) {
		Rect2 left_aabb = left.GetAABB();
		Rect2 right_aabb = right.GetAABB();
		return left_aabb.GetLD()(0) < right_aabb.GetLD()(0);
	});

	//S}`Ì½è»è
	for (CircleGeometry& circle : circles_)
	{
		TraverseAllSub(circle);
	}

	std::string message;
	message += std::to_string(circles_.size());
	Log::OutputTrivial(message);

	collision_comps_.clear();
	circles_.clear();

}

void CollisionManager::NoticeEachOther(ComponentHandle<CollisionComponent> comp1, ComponentHandle<CollisionComponent> comp2)
{
	comp1->hit_comps_.push_back(comp2);
	comp2->hit_comps_.push_back(comp1);
}

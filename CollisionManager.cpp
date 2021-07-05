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
	//�􉽍��W�̒ǉ�
	for (auto& comp : collision_comps_)
	{
		comp->AddGeometryToManager(*this);
	}
	
	//AABB�̍�x���W�����ŕ��ёւ�
	std::sort(circles_.begin(), circles_.end(), [](const CircleGeometry& left, const CircleGeometry& right) {
		Rect2 left_aabb = left.GetAABB();
		Rect2 right_aabb = right.GetAABB();
		return left_aabb.GetLD()(0) < right_aabb.GetLD()(0);
	});

	//�S�}�`�̓����蔻��
	for (CircleGeometry& circle : circles_)
	{
		TraverseAllSub(circle);
	}

	collision_comps_.clear();
}

void CollisionManager::NoticeEachOther(ComponentHandle<CollisionComponent> comp1, ComponentHandle<CollisionComponent> comp2)
{
	comp1->hit_comps_.push_back(comp2);
	comp1->hit_comps_.push_back(comp1);
}

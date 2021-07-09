#include "stdafx.h"
#include "CollisionManager.h"

#include "CollisionComponent.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::TraverseAll()
{
	//AABB�̍�x���W�����ŕ��ёւ�
	std::sort(circles_.begin(), circles_.end(), [](const CircleGeometry& left, const CircleGeometry& right) {
		Rect2 left_aabb = left.GetAABB();
		Rect2 right_aabb = right.GetAABB();
		return left_aabb.GetLD()(0) < right_aabb.GetLD()(0);
	});
	//�SCollisionComponent�̏W��
	std::set<ComponentHandle<CollisionComponent>> all_comps;

	//�S�}�`�̓����蔻��
	for (CircleGeometry& circle : circles_)
	{
		all_comps.insert(circle.GetParent());
		TraverseAllSub(circle);
	}

	//�SCollisionComponent��CheckHitComponent���Ăяo��
	for (auto comp : all_comps)
	{
		comp->CheckHitComponent();
		comp->hit_comps_.clear();
	}

	circles_.clear();

}

void CollisionManager::NoticeEachOther(ComponentHandle<CollisionComponent> comp1, ComponentHandle<CollisionComponent> comp2)
{
	comp1->hit_comps_.insert(comp2);
	comp2->hit_comps_.insert(comp1);
}

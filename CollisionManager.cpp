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
	//AABBの左x座標昇順で並び替え
	std::sort(circles_.begin(), circles_.end(), [](const CircleGeometry& left, const CircleGeometry& right) {
		Rect2 left_aabb = left.GetAABB();
		Rect2 right_aabb = right.GetAABB();
		return left_aabb.GetLD()(0) < right_aabb.GetLD()(0);
	});
	//全CollisionComponentの集合
	std::set<ComponentHandle<CollisionComponent>> all_comps;

	//全図形の当たり判定
	for (CircleGeometry& circle : circles_)
	{
		all_comps.insert(circle.GetParent());
		TraverseAllSub(circle);
	}

	//全CollisionComponentのCheckHitComponentを呼び出す
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

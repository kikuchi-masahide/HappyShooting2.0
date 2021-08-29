#include "stdafx.h"
#include "CollisionManager.h"

#include "CollisionComponent.h"
#include "CircleGeometry.h"
#include "PolygonGeometry.h"

using CircleGeometry_AABB = std::pair<CircleGeometry*, Rect2>;
using PolygonGeometry_AABB = std::pair<PolygonGeometry*, Rect2>;

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::TraverseAll()
{
	//AABBの左x座標昇順で並び替え
	std::sort(circles_.begin(), circles_.end(), [](const CircleGeometry_AABB& left, const CircleGeometry_AABB& right) {
		const Rect2& left_aabb = left.second;
		const Rect2& right_aabb = right.second;
		return left_aabb.GetLD()(0) < right_aabb.GetLD()(0);
	});
	std::sort(polygons_.begin(), polygons_.end(), [](const PolygonGeometry_AABB& left, const PolygonGeometry_AABB& right) {
		const Rect2& left_aabb = left.second;
		const Rect2& right_aabb = right.second;
		return left_aabb.GetLD()(0) < right_aabb.GetLD()(0);
	});
	//全CollisionComponentの集合
	std::set<ComponentHandle<CollisionComponent>> all_comps;

	//幾何配列1,2,3,4,5 3[5]との比較：
	//TraverseAll_less(3[5],array1)
	//TraverseAll_less(3[5],array2)
	//TraverseAll_same(3[5],array3,5)
	//TraverseAll_leq(3[5],array4)
	//TraverseAll_leq(3[5],array5)

	//全図形の当たり判定
	for (unsigned int n = 0; n < circles_.size(); n++)
	{
		all_comps.insert(circles_[n].first->GetParent());
		TraverseAllSub_same(circles_, n);
		TraverseAllSub_leq<CircleGeometry,PolygonGeometry>(circles_[n].first, circles_[n].second, polygons_);
	}
	for (unsigned int n = 0; n < polygons_.size(); n++)
	{
		all_comps.insert(polygons_[n].first->GetParent());
		TraverseAllSub_less(polygons_[n].first, polygons_[n].second, circles_);
		TraverseAllSub_same(polygons_, n);
	}

	//全CollisionComponentのCheckHitComponentを呼び出す
	for (auto comp : all_comps)
	{
		comp->CheckHitComponent();
		comp->hit_comps_.clear();
	}

	circles_.clear();

}

void CollisionManager::AddCircleGeometry(CircleGeometry* circle)
{
	circles_.emplace_back(circle, circle->GetAABB());
}

void CollisionManager::AddPolygonGeometry(PolygonGeometry* polygon)
{
	polygons_.emplace_back(polygon, polygon->GetAABB());
}

void CollisionManager::NoticeEachOther(ComponentHandle<CollisionComponent> comp1, ComponentHandle<CollisionComponent> comp2)
{
	comp1->hit_comps_.insert(comp2);
	comp2->hit_comps_.insert(comp1);
}

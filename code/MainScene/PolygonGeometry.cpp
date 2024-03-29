#include "PolygonGeometry.h"

#include "CircleGeometry.h"
#include "CupsuleGeometry.h"

PolygonGeometry::PolygonGeometry(ComponentHandle<CollisionComponent> parent_comp, unsigned int points_num)
	:ICollisionGeometry(parent_comp)
{
	points_.resize(points_num);
}

PolygonGeometry::PolygonGeometry(const PolygonGeometry& polygon)
	:ICollisionGeometry(polygon.GetParent()),
	points_(polygon.points_)
{
}

PolygonGeometry::PolygonGeometry()
	:ICollisionGeometry(ComponentHandle<CollisionComponent>())
{
}

bool PolygonGeometry::Dispatch(ICollisionGeometry* geometry)
{
	return geometry->IsInCollision(this);
}

bool PolygonGeometry::IsInCollision(CircleGeometry* circle)
{
	auto circle_center = circle->center_;
	auto circle_radius = circle->radius_;
	//各辺と円の当たり判定
	//円の中心との距離が半径以下になる辺が一つでも存在すれば衝突
	for (int n = 0; n < points_.size() - 1; n++)
	{
		double dist2 = ICollisionGeometry::Dist2(circle_center, points_[n], points_[n + 1]);
		if (dist2 <= circle_radius * circle_radius)
		{
			return true;
		}
	}
	double dist2 = ICollisionGeometry::Dist2(circle_center, points_.back(), points_[0]);
	if (dist2 <= circle_radius * circle_radius)
	{
		return true;
	}
	//円が多角形の内部に含まれるか否かを判定
	//すべての辺から見て円の中心が左側にいれば衝突
	for (int n = 0; n < points_.size() - 1; n++)
	{
		if (!ICollisionGeometry::IsPointOnLeft(circle_center, points_[n], points_[n + 1]))
		{
			return false;
		}
	}
	return ICollisionGeometry::IsPointOnLeft(circle_center, points_.back(), points_[0]);
}

bool PolygonGeometry::IsInCollision(CupsuleGeometry* cupsule)
{
	//味方が敵に多角形の当たり判定を出すことはないため
	return false;
}

bool PolygonGeometry::IsInCollision(PolygonGeometry* polygon)
{
	//味方が敵に多角形の当たり判定を出すことはないため
	return false;
}
#include "CupsuleGeometry.h"

#include "CircleGeometry.h"
#include "PolygonGeometry.h"

CupsuleGeometry::CupsuleGeometry(ComponentHandle<CollisionComponent> parent_comp)
	:ICollisionGeometry(parent_comp),
	r_(0)
{
}

CupsuleGeometry::CupsuleGeometry()
	:ICollisionGeometry(ComponentHandle<CollisionComponent>()),
	r_(0)
{
}

CupsuleGeometry::~CupsuleGeometry()
{
}

bool CupsuleGeometry::Dispatch(ICollisionGeometry* geometry)
{
	return geometry->IsInCollision(this);
}

bool CupsuleGeometry::IsInCollision(CircleGeometry* circle)
{
	double dist2 = Dist2(circle->center_, a_, b_);
	double circle_r = circle->radius_;
	return (dist2 <= (circle_r + r_) * (circle_r + r_));
}

bool CupsuleGeometry::IsInCollision(CupsuleGeometry* cupsule)
{
	//味方が敵にカプセル型の当たり判定を出すことはないため
	return false;
}

bool CupsuleGeometry::IsInCollision(PolygonGeometry* polygon)
{
	//味方が敵にカプセル型の当たり判定を出すことはないため
	return false;
}

#include "stdafx.h"
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

bool CupsuleGeometry::IsCrossing(CircleGeometry& circle)
{
	double dist2 = Dist2(circle.center_, a_, b_);
	return (dist2 <= (circle.radius_ + r_) * (circle.radius_ + r_));
}

bool CupsuleGeometry::IsCrossing(PolygonGeometry& polygon)
{
	//Žb’è“I‚É
	return false;
}

bool CupsuleGeometry::IsCrossing(CupsuleGeometry& cupsule)
{
	//Žb’è“I‚É
	return false;
}

double CupsuleGeometry::Dist2(MatVec::Vector2 p, MatVec::Vector2 a, MatVec::Vector2 b)
{
	//d=(b-a)/|b-a|
	MatVec::Vector2 d = b - a;
	d.Normalize();
	double ddotap = MatVec::Dot(d, p - a);
	if (ddotap < 0)
	{
		return (p - a).Norm2();
	}
	double ddotbp = MatVec::Dot(d, p - b);
	if (ddotbp > 0)
	{
		return (p - b).Norm2();
	}
	double cross = MatVec::Cross(d, p - a);
	return cross * cross;
}

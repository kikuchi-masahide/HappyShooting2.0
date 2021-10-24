#include "stdafx.h"
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
	//Še•Ó‚Æ‰~‚Ì“–‚½‚è”»’è
	//‰~‚Ì’†S‚Æ‚Ì‹——£‚ª”¼ŒaˆÈ‰º‚É‚È‚é•Ó‚ªˆê‚Â‚Å‚à‘¶İ‚·‚ê‚ÎÕ“Ë
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
	//‰~‚ª‘½ŠpŒ`‚Ì“à•”‚ÉŠÜ‚Ü‚ê‚é‚©”Û‚©‚ğ”»’è
	//‚·‚×‚Ä‚Ì•Ó‚©‚çŒ©‚Ä‰~‚Ì’†S‚ª¶‘¤‚É‚¢‚ê‚ÎÕ“Ë
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
	//–¡•û‚ª“G‚É‘½ŠpŒ`‚Ì“–‚½‚è”»’è‚ğo‚·‚±‚Æ‚Í‚È‚¢‚½‚ß
	return false;
}

bool PolygonGeometry::IsInCollision(PolygonGeometry* polygon)
{
	//–¡•û‚ª“G‚É‘½ŠpŒ`‚Ì“–‚½‚è”»’è‚ğo‚·‚±‚Æ‚Í‚È‚¢‚½‚ß
	return false;
}
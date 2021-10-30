#include "CircleGeometry.h"

#include "PolygonGeometry.h"
#include "CupsuleGeometry.h"

CircleGeometry::CircleGeometry(ComponentHandle<CollisionComponent> parent_comp, MatVec::Vector2 center, double radius)
	:ICollisionGeometry(parent_comp),
	center_(center),radius_(radius)
{
}

CircleGeometry::CircleGeometry(const CircleGeometry& circle)
	:ICollisionGeometry(circle.GetParent()),center_(circle.center_),radius_(circle.radius_)
{
}

CircleGeometry::CircleGeometry()
	:center_(MatVec::Vector2(0,0)),radius_(0),ICollisionGeometry(ComponentHandle<CollisionComponent>())
{
}

CircleGeometry::~CircleGeometry()
{
}

bool CircleGeometry::Dispatch(ICollisionGeometry* geometry)
{
	return IsInCollision(this);
}

bool CircleGeometry::IsInCollision(CircleGeometry* circle)
{
	MatVec::Vector2 center2 = circle->center_;
	double radius2 = circle->radius_;
	double d2 = (center_(0) - center2(0)) * (center_(0) - center2(0)) + (center_(1) - center2(1)) * (center_(1) - center2(1));
	return (
		d2 <= (radius_ + radius2) * (radius_ + radius2)
		);
}

bool CircleGeometry::IsInCollision(CupsuleGeometry* cupsule)
{
	double dist2 = ICollisionGeometry::Dist2(center_, cupsule->a_, cupsule->b_);
	double cupsule_r = cupsule->r_;
	return (dist2 <= (cupsule_r + radius_) * (cupsule_r + radius_));
}

bool CircleGeometry::IsInCollision(PolygonGeometry* polygon)
{
	auto& points = polygon->points_;
	//Še•Ó‚Æ‰~‚Ì“–‚½‚è”»’è
	//‰~‚Ì’†S‚Æ‚Ì‹——£‚ª”¼ŒaˆÈ‰º‚É‚È‚é•Ó‚ªˆê‚Â‚Å‚à‘¶İ‚·‚ê‚ÎÕ“Ë
	for (int n = 0; n < points.size() - 1; n++)
	{
		double dist2 = ICollisionGeometry::Dist2(center_, points[n], points[n + 1]);
		if (dist2 <= radius_ * radius_)
		{
			return true;
		}
	}
	double dist2 = ICollisionGeometry::Dist2(center_, points.back(), points[0]);
	if (dist2 <= radius_ * radius_)
	{
		return true;
	}
	//‰~‚ª‘½ŠpŒ`‚Ì“à•”‚ÉŠÜ‚Ü‚ê‚é‚©”Û‚©‚ğ”»’è
	//‚·‚×‚Ä‚Ì•Ó‚©‚çŒ©‚Ä‰~‚Ì’†S‚ª¶‘¤‚É‚¢‚ê‚ÎÕ“Ë
	for (int n = 0; n < points.size() - 1; n++)
	{
		if (!ICollisionGeometry::IsPointOnLeft(center_, points[n], points[n + 1]))
		{
			return false;
		}
	}
	return ICollisionGeometry::IsPointOnLeft(center_, points.back(), points[0]);
}

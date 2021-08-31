#include "stdafx.h"
#include "PolygonGeometry.h"

#include "CircleGeometry.h"

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

bool PolygonGeometry::IsCrossing(CircleGeometry& circle)
{
	//Še•Ó‚Æ‰~‚Ì“–‚½‚è”»’è
	//‰~‚Ì’†S‚Æ‚Ì‹——£‚ª”¼ŒaˆÈ‰º‚É‚È‚é•Ó‚ªˆê‚Â‚Å‚à‘¶İ‚·‚ê‚ÎÕ“Ë
	for (int n = 0; n < points_.size()-1; n++)
	{
		double dist2 = Dist2(circle.center_, points_[n], points_[n + 1]);
		if (dist2 <= circle.radius_ * circle.radius_)
		{
			return true;
		}
	}
	double dist2 = Dist2(circle.center_, points_.back(), points_[0]);
	if (dist2 <= circle.radius_ * circle.radius_)
	{
		return true;
	}
	//‰~‚ª‘½ŠpŒ`‚Ì“à•”‚ÉŠÜ‚Ü‚ê‚é‚©”Û‚©‚ğ”»’è
	//‚·‚×‚Ä‚Ì•Ó‚©‚çŒ©‚Ä‰~‚Ì’†S‚ª¶‘¤‚É‚¢‚ê‚ÎÕ“Ë
	for (int n = 0; n < points_.size() - 1; n++)
	{
		if (!IsPointOnLeft(circle.center_, points_[n], points_[n + 1]))
		{
			return false;
		}
	}
	return IsPointOnLeft(circle.center_, points_.back(), points_[0]);
}

bool PolygonGeometry::IsCrossing(PolygonGeometry& polygon)
{
	//¡Polygon‚Í“G‹@‚Ì‚İ‚ª‚Â“–‚½‚è”»’è‚È‚Ì‚ÅC‚Æ‚è‚ ‚¦‚¸false
	return false;
}

double PolygonGeometry::Dist2(MatVec::Vector2 p, MatVec::Vector2 a, MatVec::Vector2 b)
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

bool PolygonGeometry::IsPointOnLeft(MatVec::Vector2 p, MatVec::Vector2 a, MatVec::Vector2 b)
{
	return (MatVec::Cross(b - a, p - a) > 0);
}

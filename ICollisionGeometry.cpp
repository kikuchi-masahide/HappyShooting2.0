#include "stdafx.h"
#include "ICollisionGeometry.h"

double ICollisionGeometry::Dist2(MatVec::Vector2 p, MatVec::Vector2 a, MatVec::Vector2 b)
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

bool ICollisionGeometry::IsPointOnLeft(MatVec::Vector2 p, MatVec::Vector2 a, MatVec::Vector2 b)
{
	return (MatVec::Cross(b - a, p - a) > 0);
}

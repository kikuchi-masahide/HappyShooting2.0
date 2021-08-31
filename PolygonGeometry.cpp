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
	//�e�ӂƉ~�̓����蔻��
	//�~�̒��S�Ƃ̋��������a�ȉ��ɂȂ�ӂ���ł����݂���ΏՓ�
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
	//�~�����p�`�̓����Ɋ܂܂�邩�ۂ��𔻒�
	//���ׂĂ̕ӂ��猩�ĉ~�̒��S�������ɂ���ΏՓ�
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
	//��Polygon�͓G�@�݂̂��������蔻��Ȃ̂ŁC�Ƃ肠����false
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

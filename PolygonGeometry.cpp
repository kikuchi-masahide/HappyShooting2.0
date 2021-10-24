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
	//�e�ӂƉ~�̓����蔻��
	//�~�̒��S�Ƃ̋��������a�ȉ��ɂȂ�ӂ���ł����݂���ΏՓ�
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
	//�~�����p�`�̓����Ɋ܂܂�邩�ۂ��𔻒�
	//���ׂĂ̕ӂ��猩�ĉ~�̒��S�������ɂ���ΏՓ�
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
	//�������G�ɑ��p�`�̓����蔻����o�����Ƃ͂Ȃ�����
	return false;
}

bool PolygonGeometry::IsInCollision(PolygonGeometry* polygon)
{
	//�������G�ɑ��p�`�̓����蔻����o�����Ƃ͂Ȃ�����
	return false;
}
#include "stdafx.h"
#include "CircleGeometry.h"

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

bool CircleGeometry::IsCrossing(const CircleGeometry& circle2)
{
	MatVec::Vector2 center2 = circle2.center_;
	double radius2 = circle2.radius_;
	double d2 = (center_(0) - center2(0)) * (center_(0) - center2(0)) + (center_(1) - center2(1)) * (center_(1) - center2(1));
	return (
		d2 <= (radius_ + radius2) * (radius_ + radius2)
	);
}

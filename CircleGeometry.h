#pragma once
#include "ICollisionGeometry.h"

//円形領域を表す当たり判定図形(内部含)
class CircleGeometry final:
    public ICollisionGeometry
{
public:
    CircleGeometry(ComponentHandle<CollisionComponent> parent_comp, MatVec::Vector2 center, double radius);
    CircleGeometry(const CircleGeometry& circle);
    ~CircleGeometry();
    MatVec::Vector2 center_;
    double radius_;
    Rect2 GetAABB() const override;
    /// <summary>
    /// この円と交差・衝突しているか否かを返す
    /// </summary>
    bool IsCrossing(const CircleGeometry& circle2);
};


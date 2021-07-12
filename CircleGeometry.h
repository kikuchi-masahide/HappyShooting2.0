#pragma once
#include "ICollisionGeometry.h"

//円形領域を表す当たり判定図形(内部含)
class CircleGeometry final:
    public ICollisionGeometry
{
public:
    CircleGeometry(ComponentHandle<CollisionComponent> parent_comp, MatVec::Vector2 center, double radius);
    CircleGeometry(const CircleGeometry& circle);
    CircleGeometry();
    ~CircleGeometry();
    MatVec::Vector2 center_;
    double radius_;
    inline Rect2 GetAABB() const override
    {
        double x = center_(0);
        double y = center_(1);
        return Rect2(x - radius_, x + radius_, y - radius_, y + radius_);
    };
    /// <summary>
    /// この円と交差・衝突しているか否かを返す
    /// </summary>
    bool IsCrossing(const CircleGeometry& circle2);
};


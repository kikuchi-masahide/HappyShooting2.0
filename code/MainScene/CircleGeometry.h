#pragma once
#include "ICollisionGeometry.h"

class PolygonGeometry;
class CupsuleGeometry;

//‰~Œ`—Ìˆæ‚ğ•\‚·“–‚½‚è”»’è}Œ`(“à•”ŠÜ)
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
    inline Rect2 GetAABB() override
    {
        double x = center_(0);
        double y = center_(1);
        return Rect2(x - radius_, x + radius_, y - radius_, y + radius_);
    };
    bool Dispatch(ICollisionGeometry* geometry) override;
    bool IsInCollision(CircleGeometry* circle) override;
    bool IsInCollision(CupsuleGeometry* cupsule) override;
    bool IsInCollision(PolygonGeometry* polygon) override;
};


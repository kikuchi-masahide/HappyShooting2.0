#pragma once
#include "ICollisionGeometry.h"

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
    Rect2 GetAABB() const override;
    /// <summary>
    /// ‚±‚Ì‰~‚ÆŒğ·EÕ“Ë‚µ‚Ä‚¢‚é‚©”Û‚©‚ğ•Ô‚·
    /// </summary>
    bool IsCrossing(const CircleGeometry& circle2);
};


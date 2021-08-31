#pragma once
#include "ICollisionGeometry.h"

class CircleGeometry;
class PolygonGeometry;

class CupsuleGeometry :
    public ICollisionGeometry
{
public:
    CupsuleGeometry(ComponentHandle<CollisionComponent> parent_comp);
    CupsuleGeometry();
    ~CupsuleGeometry();
    //�J�v�Z���̓���������2�[�_
    MatVec::Vector2 a_, b_;
    //�J�v�Z���̔��a
    double r_;
    inline Rect2 GetAABB() {
        return Rect2(min(a_(0), b_(0)) - r_, max(a_(0), b_(0)) + r_, min(a_(1), b_(1)) - r_, max(a_(1), b_(1)) + r_);
    }
    bool IsCrossing(CircleGeometry& circle);
    bool IsCrossing(PolygonGeometry& polygon);
    bool IsCrossing(CupsuleGeometry& cupsule);
private:
    //�_p�Ɛ���ab�̋�����2��
    static double Dist2(MatVec::Vector2 p, MatVec::Vector2 a, MatVec::Vector2 b);
};


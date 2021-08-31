#pragma once
#include "ICollisionGeometry.h"

class CircleGeometry;

//���p�`(������)
class PolygonGeometry final:
    public ICollisionGeometry
{
public:
    /// <param name="points_num">���_��</param>
    PolygonGeometry(ComponentHandle<CollisionComponent> parent_comp,unsigned int points_num);
    PolygonGeometry(const PolygonGeometry& polygon);
    PolygonGeometry();
    //���_(�����v���)
    std::vector<MatVec::Vector2> points_;
    inline Rect2 GetAABB() override
    {
        //���p�`�ƌ����Ă���񂾂���C3���_�ȏ㎝���Ă��Ă���
        BOOST_ASSERT(points_.size() >= 3);
        double xmin = 1e14;
        double xmax = -1e14;
        double ymin = 1e14;
        double ymax = -1e14;
        for (MatVec::Vector2& point : points_)
        {
            xmin = min(xmin, point(0));
            xmax = max(xmax, point(0));
            ymin = min(ymin, point(1));
            ymax = max(ymax, point(1));
        }
        return Rect2(xmin, xmax, ymin, ymax);
    }
    bool IsCrossing(CircleGeometry& circle);
    bool IsCrossing(PolygonGeometry& polygon);
private:
    //�_p�Ɛ���ab�̋�����2��
    static double Dist2(MatVec::Vector2 p, MatVec::Vector2 a, MatVec::Vector2 b);
    //���̓_������ab�̍����ɂ��邩�ۂ�����
    static bool IsPointOnLeft(MatVec::Vector2 p, MatVec::Vector2 a, MatVec::Vector2 b);
};


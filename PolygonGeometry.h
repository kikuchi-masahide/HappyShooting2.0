#pragma once
#include "ICollisionGeometry.h"

class CircleGeometry;

//多角形(内部含)
class PolygonGeometry final:
    public ICollisionGeometry
{
public:
    /// <param name="points_num">頂点数</param>
    PolygonGeometry(ComponentHandle<CollisionComponent> parent_comp,unsigned int points_num);
    PolygonGeometry(const PolygonGeometry& polygon);
    PolygonGeometry();
    //頂点(反時計回り)
    std::vector<MatVec::Vector2> points_;
    inline Rect2 GetAABB() override
    {
        //多角形と言っているんだから，3頂点以上持っていてくれ
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
    //点pと線分abの距離の2乗
    static double Dist2(MatVec::Vector2 p, MatVec::Vector2 a, MatVec::Vector2 b);
    //この点が直線abの左側にあるか否か判定
    static bool IsPointOnLeft(MatVec::Vector2 p, MatVec::Vector2 a, MatVec::Vector2 b);
};


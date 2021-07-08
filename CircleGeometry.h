#pragma once
#include "ICollisionGeometry.h"

//�~�`�̈��\�������蔻��}�`(������)
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
    /// ���̉~�ƌ����E�Փ˂��Ă��邩�ۂ���Ԃ�
    /// </summary>
    bool IsCrossing(const CircleGeometry& circle2);
};


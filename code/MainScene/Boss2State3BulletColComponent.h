#pragma once
#include "CollisionComponent.h"

#include "CircleGeometry.h"

class Boss2State3BulletColComponent :
    public CollisionComponent
{
public:
    Boss2State3BulletColComponent(GameObjectHandle obj, boost::shared_ptr<CollisionManager> manager);
    ~Boss2State3BulletColComponent();
    void Update();
    void CheckHitComponent();
    //�����蔻����s�����ۂ�
    bool active_;
private:
    static const double radius_;
    CircleGeometry circle_;
};


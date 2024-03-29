#pragma once
#include "CollisionComponent.h"

#include "PolygonGeometry.h"

class CollisionManager;

class Boss1BulletCollisionComponent :
    public CollisionComponent
{
public:
    Boss1BulletCollisionComponent(GameObjectHandle obj, boost::shared_ptr<CollisionManager> collision_manager);
    ~Boss1BulletCollisionComponent();
    void Update() override;
    void CheckHitComponent() override;
private:
    PolygonGeometry polygon_;
    //object座標=(0,0)の時の当たり判定の座標
    PolygonGeometry template_;
};


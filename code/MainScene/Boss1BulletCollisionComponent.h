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
    //objectÀ•W=(0,0)‚Ì‚Ì“–‚½‚è”»’è‚ÌÀ•W
    PolygonGeometry template_;
};


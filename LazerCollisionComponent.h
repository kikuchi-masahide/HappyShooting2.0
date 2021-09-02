#pragma once
#include "CollisionComponent.h"

#include "CupsuleGeometry.h"

class LazerCollisionComponent :
    public CollisionComponent
{
public:
    LazerCollisionComponent(GameObjectHandle obj, boost::shared_ptr<CollisionManager> manager);
    ~LazerCollisionComponent();
    void Update() override;
    void CheckHitComponent() override;
    CupsuleGeometry cupsule_;
};


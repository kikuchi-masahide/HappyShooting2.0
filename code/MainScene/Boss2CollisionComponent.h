#pragma once
#include "CollisionComponent.h"
#include "CircleGeometry.h"

class Boss2MediatorComponent;

class Boss2CollisionComponent :
    public CollisionComponent
{
public:
    Boss2CollisionComponent(GameObjectHandle handle, boost::shared_ptr<CollisionManager> manager, ComponentHandle<Boss2MediatorComponent> med);
    virtual ~Boss2CollisionComponent();
    void Update() override;
    void CheckHitComponent() override;
private:
    CircleGeometry circle_;
    ComponentHandle<Boss2MediatorComponent> med_;
};


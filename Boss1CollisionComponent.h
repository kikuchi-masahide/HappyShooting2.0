#pragma once
#include "CollisionComponent.h"

#include "PolygonGeometry.h"

class Boss1MediatorComponent;

class Boss1CollisionComponent :
    public CollisionComponent
{
public:
    Boss1CollisionComponent(GameObjectHandle handle, boost::shared_ptr<CollisionManager> manager, ComponentHandle<Boss1MediatorComponent> mediator);
    ~Boss1CollisionComponent();
    void Update() override;
    void CheckHitComponent() override;
private:
    ComponentHandle<Boss1MediatorComponent> mediator_;
    PolygonGeometry polygon_[4];
    //polygon_ÇÃç¿ïWê›íËÇÇ∑ÇÈ
    void SetPolygonCoord();
};


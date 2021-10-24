#pragma once
#include "CollisionComponent.h"

#include "PolygonGeometry.h"

class Boss1MediatorComponent;

//TODO:HealthComponent作ったらEnemyBodyCollisionComponentに鞍替えする
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
    //polygon_の座標設定をする
    void SetPolygonCoord();
};


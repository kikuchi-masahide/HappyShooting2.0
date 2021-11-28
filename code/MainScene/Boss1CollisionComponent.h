#pragma once
#include "EnemyBodyCollisionComponent.h"

#include "PolygonGeometry.h"

class Boss1MediatorComponent;
class ScoreManager;

class Boss1CollisionComponent :
    public EnemyBodyCollisionComponent<Boss1MediatorComponent>
{
public:
    Boss1CollisionComponent(GameObjectHandle handle, boost::shared_ptr<CollisionManager> manager, boost::shared_ptr<ScoreManager> score_manager, ComponentHandle<Boss1MediatorComponent> mediator);
    ~Boss1CollisionComponent();
    void Update() override;
private:
    ComponentHandle<Boss1MediatorComponent> mediator_;
    PolygonGeometry polygon_[4];
    //polygon_ÇÃç¿ïWê›íËÇÇ∑ÇÈ
    void SetPolygonCoord();
};


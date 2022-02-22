#pragma once
#include "EnemyBodyCollisionComponent.h"

#include "EnemyHealthComponent.h"

class Enemy6CollisionComponent :
    public EnemyBodyCollisionComponent<EnemyHealthComponent>
{
public:
    Enemy6CollisionComponent(GameObjectHandle object, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<ScoreManager> score_manager, ComponentHandle<EnemyHealthComponent> health_component, int time);
    ~Enemy6CollisionComponent();
    void Update() override;
private:
    int time_;
    PolygonGeometry polygon_;
};


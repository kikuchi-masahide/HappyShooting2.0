#pragma once
#include "EnemyBodyCollisionComponent.h"

#include "CircleGeometry.h"

class EnemyHealthComponent;
class ScoreManager;

class Enemy3CollisionComponent :
    public EnemyBodyCollisionComponent
{
public:
    Enemy3CollisionComponent(GameObjectHandle object, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<ScoreManager> score_manager, ComponentHandle<EnemyHealthComponent> health);
    ~Enemy3CollisionComponent();
    void Update() override;
    static constexpr double damage_ = 200;
private:
    CircleGeometry circle_;
};


#pragma once
#include "CollisionComponent.h"

class EnemyHealthComponent;
class ScoreManager;

class Enemy3CollisionComponent :
    public CollisionComponent
{
public:
    Enemy3CollisionComponent(GameObjectHandle object, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<ScoreManager> score_manager, ComponentHandle<EnemyHealthComponent> health);
    ~Enemy3CollisionComponent();
    void Update() override;
    void CheckHitComponent() override;
    static constexpr double damage_ = 200;
private:
    CircleGeometry circle_;
    ComponentHandle<EnemyHealthComponent> health_component_;
    boost::shared_ptr<ScoreManager> score_manager_;
};


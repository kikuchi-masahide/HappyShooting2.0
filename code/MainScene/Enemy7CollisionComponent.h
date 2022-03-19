#pragma once
#include "EnemyBodyCollisionComponent.h"

#include "EnemyHealthComponent.h"
#include "CircleGeometry.h"

class Enemy7CollisionComponent :
    public EnemyBodyCollisionComponent<EnemyHealthComponent>
{
public:
    Enemy7CollisionComponent(GameObjectHandle object, boost::shared_ptr<CollisionManager> col, boost::shared_ptr<ScoreManager> score, ComponentHandle<EnemyHealthComponent> health);
    ~Enemy7CollisionComponent();
    void Update() override;
public:
    CircleGeometry circle_;
    CircleGeometry circle_small_[2];
};


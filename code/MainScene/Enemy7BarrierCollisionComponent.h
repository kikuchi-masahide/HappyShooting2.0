#pragma once
#include "CollisionComponent.h"

#include "CircleGeometry.h"

class LayerManager;

/// <summary>
/// Enemy7のバリアの当たり判定、ヘルス管理を行う
/// </summary>
class Enemy7BarrierCollisionComponent :
    public CollisionComponent
{
public:
    Enemy7BarrierCollisionComponent(GameObjectHandle handle, boost::shared_ptr<CollisionManager> manager, boost::shared_ptr<LayerManager> layer);
    ~Enemy7BarrierCollisionComponent();
    void Update() override;
    void CheckHitComponent() override;
    //DrawHealthBarComponent用
    double GetHealthRate();
private:
    boost::shared_ptr<CollisionManager> collision_;
    boost::shared_ptr<LayerManager> layer_;
    CircleGeometry circle_;
    void InverseBullet(ComponentHandle<CollisionComponent> comp);
    unsigned int health_;
};


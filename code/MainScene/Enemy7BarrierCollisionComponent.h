#pragma once
#include "CollisionComponent.h"

#include "CircleGeometry.h"

class LayerManager;

/// <summary>
/// Enemy7�̃o���A�̓����蔻��A�w���X�Ǘ����s��
/// </summary>
class Enemy7BarrierCollisionComponent :
    public CollisionComponent
{
public:
    Enemy7BarrierCollisionComponent(GameObjectHandle handle, boost::shared_ptr<CollisionManager> manager, boost::shared_ptr<LayerManager> layer);
    ~Enemy7BarrierCollisionComponent();
    void Update() override;
    void CheckHitComponent() override;
    //DrawHealthBarComponent�p
    double GetHealthRate();
private:
    boost::shared_ptr<CollisionManager> collision_;
    boost::shared_ptr<LayerManager> layer_;
    CircleGeometry circle_;
    void InverseBullet(ComponentHandle<CollisionComponent> comp);
    unsigned int health_;
};


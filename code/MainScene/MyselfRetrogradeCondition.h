#pragma once
#include "MyselfConditionBase.h"

class MyselfRetrogradeCondition :
    public MyselfConditionBase
{
public:
    MyselfRetrogradeCondition(GameObjectHandle handle, ComponentHandle<MyselfMediatorComponent> mediator, unsigned int speed);
    ~MyselfRetrogradeCondition();
    void Update() override;
    unsigned int GetDamaged(unsigned int attack) override;
    bool IsShooterActive();
    void CheckHitComponent(std::set<ComponentHandle<CollisionComponent>>& hit_comps_) override;
private:
    unsigned int speed_;
};


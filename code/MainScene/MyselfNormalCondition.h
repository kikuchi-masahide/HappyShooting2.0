#pragma once
#include "MyselfConditionBase.h"

class Scene;

class MyselfNormalCondition :
    public MyselfConditionBase
{
public:
    MyselfNormalCondition(GameObjectHandle handle, ComponentHandle<MyselfMediatorComponent> mediator);
    ~MyselfNormalCondition();
    void Update() override;
    unsigned int GetDamaged(unsigned int attack) override;
    bool IsInvincible() override;
private:
    Scene* scene_;
    //1tick‚ ‚½‚è‚ÌˆÚ“®‹——£
    constexpr static double moving_dist_ = 3.45;
};


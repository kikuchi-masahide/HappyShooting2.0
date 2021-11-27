#pragma once
#include "MyselfConditionBase.h"

#include "../Engine/Math/Math.h"

class MyselfRevivingCondition :
    public MyselfConditionBase
{
public:
    MyselfRevivingCondition(GameObjectHandle handle, ComponentHandle<MyselfMediatorComponent> mediator);
    ~MyselfRevivingCondition();
    void Update() override;
    unsigned int GetDamaged(unsigned int attack) override;
    bool IsInvincible() override;
private:
    Scene* scene_;
    //•œŠˆ‰‰o‚É‰½tick‚©‚¯‚é‚©
    static constexpr unsigned int whole_time_ = 180;
    //ƒ¿‚Ì1tick“–‚½‚è‚ÌˆÊ‘Š•Ï‰»—Ê
    static constexpr double delta_alpha_theta_ = PI * 6 / whole_time_;
    //‚Í‚¶‚ß‚ÄUpdate‚ªŒÄ‚Ño‚³‚ê‚½‚Æ‚«0
    unsigned int counter_;
    //1tick‚ ‚½‚è‚ÌˆÚ“®‹——£
    constexpr static double moving_dist_ = 3.45;
};


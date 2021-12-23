#pragma once
#include "MyselfConditionBase.h"

//残機0の状態で被弾すると，オブジェクト自体は生きているが不可視で攻撃も当たらない死んだ状態になる
class MyselfDeadCondition :
    public MyselfConditionBase
{
public:
    MyselfDeadCondition(GameObjectHandle handle, ComponentHandle<MyselfMediatorComponent> mediator);
    ~MyselfDeadCondition();
    void Update() override;
    unsigned int GetDamaged(unsigned int attack) override;
    bool IsInvincible() override;
    bool IsShooterActive() override;
};


#pragma once
#include "MyselfConditionBase.h"

//�c�@0�̏�ԂŔ�e����ƁC�I�u�W�F�N�g���̂͐����Ă��邪�s���ōU����������Ȃ����񂾏�ԂɂȂ�
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


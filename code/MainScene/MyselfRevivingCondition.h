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
    //�������o�ɉ�tick�����邩
    static constexpr unsigned int whole_time_ = 180;
    //����1tick������̈ʑ��ω���
    static constexpr double delta_alpha_theta_ = PI * 6 / whole_time_;
    //�͂��߂�Update���Ăяo���ꂽ�Ƃ�0
    unsigned int counter_;
    //1tick������̈ړ�����
    constexpr static double moving_dist_ = 3.45;
};


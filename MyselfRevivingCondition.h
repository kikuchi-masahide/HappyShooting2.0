#pragma once
#include "MyselfConditionBase.h"

#include "Math.h"

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
    //�������o�ɉ�tick�����邩
    static constexpr unsigned int whole_time_ = 120;
    //����1tick������̈ʑ��ω���
    static constexpr double delta_alpha_theta_ = 4 * PI / whole_time_;
    //1tick�������y����
    static constexpr double delta_y_ = 3.45;
    //�ŏI�I��y���W
    static constexpr double last_y_ = -275;
    //�͂��߂�Update���Ăяo���ꂽ�Ƃ�0
    unsigned int counter_;
};


#pragma once
#include "MyselfConditionBase.h"

#include "code/Engine/Math/Math.h"

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
    //復活演出に何tickかけるか
    static constexpr unsigned int whole_time_ = 180;
    //αの1tick当たりの位相変化量
    static constexpr double delta_alpha_theta_ = PI * 6 / whole_time_;
    //1tickあたりのy増分
    static constexpr double delta_y_ = 3.45 / 2;
    //最終的なy座標
    static constexpr double last_y_ = -275;
    //はじめてUpdateが呼び出されたとき0
    unsigned int counter_;
};


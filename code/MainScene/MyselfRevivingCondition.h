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
private:
    Scene* scene_;
    //復活演出に何tickかけるか
    static constexpr unsigned int whole_time_ = 180;
    //αの1tick当たりの位相変化量
    static constexpr double delta_alpha_theta_ = PI * 6 / whole_time_;
    //はじめてUpdateが呼び出されたとき0
    unsigned int counter_;
    //1tickあたりの移動距離
    constexpr static double moving_dist_ = 3.45;
};


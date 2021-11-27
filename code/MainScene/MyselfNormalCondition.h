#pragma once
#include "MyselfConditionBase.h"

class Scene;
class MyselfPosAdjustComponent;

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
    //1tickあたりの移動距離
    constexpr static double moving_dist_ = 3.45;
    //左辺，下辺，右辺，上辺
    //TODO:自機復活の演出を変えたらこのコンポーネントをここで持っておくか考える
    ComponentHandle<MyselfPosAdjustComponent> pos_adjust_[4];
};


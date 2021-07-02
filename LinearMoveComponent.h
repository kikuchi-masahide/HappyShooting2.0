#pragma once
#include "Component.h"

#include "GameObjectHandle.h"

//自分のオブジェクトを線形に移動させる
class LinearMoveComponent :
    public Component
{
public:
    /// <summary>
    /// 親オブジェクトを線形に移動させる
    /// </summary>
    /// <param name="object">親オブジェクト</param>
    /// <param name="d">1tick当たりの位置の変化量</param>
    /// <param name="exist_limit">|x|＞300+exist_limit,|y|＞450+exist_limitになるとオブジェクト消失</param>
    LinearMoveComponent(GameObjectHandle object, MatVec::Vector2 d, double exist_limit);
    ~LinearMoveComponent();
    void Update() override;
private:
    GameObjectHandle object_;
    MatVec::Vector2 d_;
    double exist_limit_;
};


#pragma once
#include "Component.h"

#include "GameObjectHandle.h"
#include "Math.h"

//自分のオブジェクトを線形に移動させる
class LinearMoveComponent :
    public Component
{
public:
    /// <summary>
    /// 親オブジェクトを線形に移動させる これから先画面外に現れることがないならば親オブジェクトごと死ぬ
    /// </summary>
    /// <param name="object">親オブジェクト</param>
    /// <param name="d">1tick当たりの位置の変化量</param>
    /// <param name="exist_limit">自身を含む最小の円の半径</param>
    LinearMoveComponent(GameObjectHandle object, MatVec::Vector2 d, double exist_limit);
    ~LinearMoveComponent();
    void Update() override;
private:
    MatVec::Vector2 d_;
    double exist_limit_;
};


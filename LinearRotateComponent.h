#pragma once
#include "Component.h"

#include "GameObjectHandle.h"

//自分のオブジェクトを毎フレーム一定角度回転させる
class LinearRotateComponent :
    public Component
{
public:
    /// <param name="object">回転させるオブジェクト</param>
    /// <param name="theta">毎tickの回転角度</param>
    LinearRotateComponent(GameObjectHandle object, double theta);
    ~LinearRotateComponent();
    void Update() override;
private:
    double theta_;
};


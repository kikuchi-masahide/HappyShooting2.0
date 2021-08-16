#pragma once
#include "Component.h"

#include "Math.h"

class Enemy3MoveComponent :
    public Component
{
public:
    Enemy3MoveComponent(GameObjectHandle obj, int counter0, std::function<MatVec::Vector2(double)> lambda, double angle_delta);
    ~Enemy3MoveComponent();
    void Update() override;
private:
    int counter_;
    //角度から位置を計算する関数
    std::function<MatVec::Vector2(double)> lambda_;
    //オブジェクトの角度はcounter_*angle_delta_になる
    double angle_delta_;
};


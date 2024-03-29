#pragma once
#include "../Engine/Component.h"

#include "../Engine/Math/Math.h"

class Enemy1MoveComponent :
    public Component
{
public:
    /// <param name="wait_count">生成後何tick目から動き始めるか</param>
    /// <param name="direct">1tickあたりの移動量</param>
    /// <param name="angle">1tickあたりの回転量</param>
    Enemy1MoveComponent(GameObjectHandle handle, unsigned int wait_count, MatVec::Vector2 direct, double angle);
    void Update() override;
private:
    ~Enemy1MoveComponent();
    //何tick目から動き始めるか
    unsigned int wait_count_;
    //自分が生まれてから何tick目のUpdate()か(はじめての呼び出しの間0)
    unsigned int counter_;
    //1tickあたりの移動量
    MatVec::Vector2 direct_;
    //1tickあたりの回転量
    double angle_;
};


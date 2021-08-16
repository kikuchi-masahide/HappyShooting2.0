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
    //�p�x����ʒu���v�Z����֐�
    std::function<MatVec::Vector2(double)> lambda_;
    //�I�u�W�F�N�g�̊p�x��counter_*angle_delta_�ɂȂ�
    double angle_delta_;
};


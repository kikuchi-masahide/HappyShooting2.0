#pragma once
#include "code/Engine/Component.h"

#include "code/Engine/Math/Math.h"

class Enemy1MoveComponent :
    public Component
{
public:
    /// <param name="wait_count">�����㉽tick�ڂ��瓮���n�߂邩</param>
    /// <param name="direct">1tick������̈ړ���</param>
    /// <param name="angle">1tick������̉�]��</param>
    Enemy1MoveComponent(GameObjectHandle handle, unsigned int wait_count, MatVec::Vector2 direct, double angle);
    void Update() override;
private:
    ~Enemy1MoveComponent();
    //��tick�ڂ��瓮���n�߂邩
    unsigned int wait_count_;
    //���������܂�Ă��牽tick�ڂ�Update()��(�͂��߂Ă̌Ăяo���̊�0)
    unsigned int counter_;
    //1tick������̈ړ���
    MatVec::Vector2 direct_;
    //1tick������̉�]��
    double angle_;
};


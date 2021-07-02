#pragma once
#include "Component.h"

#include "GameObjectHandle.h"

//�����̃I�u�W�F�N�g����`�Ɉړ�������
class LinearMoveComponent :
    public Component
{
public:
    /// <summary>
    /// �e�I�u�W�F�N�g����`�Ɉړ�������
    /// </summary>
    /// <param name="object">�e�I�u�W�F�N�g</param>
    /// <param name="d">1tick������̈ʒu�̕ω���</param>
    /// <param name="exist_limit">|x|��300+exist_limit,|y|��450+exist_limit�ɂȂ�ƃI�u�W�F�N�g����</param>
    LinearMoveComponent(GameObjectHandle object, MatVec::Vector2 d, double exist_limit);
    ~LinearMoveComponent();
    void Update() override;
private:
    GameObjectHandle object_;
    MatVec::Vector2 d_;
    double exist_limit_;
};


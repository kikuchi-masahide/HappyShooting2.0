#pragma once
#include "Component.h"

#include "GameObjectHandle.h"
#include "Math.h"

//�����̃I�u�W�F�N�g����`�Ɉړ�������
class LinearMoveComponent :
    public Component
{
public:
    /// <summary>
    /// �e�I�u�W�F�N�g����`�Ɉړ������� ���ꂩ����ʊO�Ɍ���邱�Ƃ��Ȃ��Ȃ�ΐe�I�u�W�F�N�g���Ǝ���
    /// </summary>
    /// <param name="object">�e�I�u�W�F�N�g</param>
    /// <param name="d">1tick������̈ʒu�̕ω���</param>
    /// <param name="exist_limit">���g���܂ލŏ��̉~�̔��a</param>
    LinearMoveComponent(GameObjectHandle object, MatVec::Vector2 d, double exist_limit);
    ~LinearMoveComponent();
    void Update() override;
private:
    MatVec::Vector2 d_;
    double exist_limit_;
};


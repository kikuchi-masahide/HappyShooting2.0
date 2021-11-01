#pragma once
#include "../Engine/Component.h"

#include "../Engine/Math/Math.h"

//��tick�I�u�W�F�N�g�ʒu�ɑ��xv_�𑫂��Cv_�ɉ����xa_�𑫂����ƂŁC�����x�I�ȓ�����������
//(���肪���邢�̂ŁC����ʂ��啝�ɊO�ɏo���炷���ɏ��ł�����)
class AcceleratedMoveComponent :
    public Component
{
public:
    /// <param name="initial_pos">�����ʒu</param>
    /// <param name="initial_v">�������x</param>
    /// <param name="a">�����x</param>
    AcceleratedMoveComponent(GameObjectHandle obj, int prio,MatVec::Vector2 initial_pos,MatVec::Vector2 initial_v,MatVec::Vector2 a);
    void Update() override;
private:
    ~AcceleratedMoveComponent();
    //Update()�ŃI�u�W�F�N�g�ʒu�ɑ������x
    MatVec::Vector2 v_;
    //�����x
    MatVec::Vector2 a_;
};


#pragma once
#include "../Engine/Component.h"

#include "../Engine/Math/Math.h"

//���@�̈ʒu���C�����̉E���̈�Ɏ��܂�悤�C������
class MyselfPosAdjustComponent :
    public Component
{
public:
    /// <summary>
    /// �_a�Cb��ʂ钼���́C�x�N�g��b-a�̉E���̗̈�Ɏ��܂�悤�C���@�̈ʒu���C������
    /// </summary>
    /// <param name="myself">���@�n���h��</param>
    MyselfPosAdjustComponent(GameObjectHandle handle, GameObjectHandle myself, MatVec::Vector2 a, MatVec::Vector2 b);
    ~MyselfPosAdjustComponent();
    void Update() override;
    //�����̒ʂ�_���C������
    void SetAnchorPoint(MatVec::Vector2 a, MatVec::Vector2 b);
private:
    MatVec::Vector2 a_, b_;
    GameObjectHandle myself_;
};


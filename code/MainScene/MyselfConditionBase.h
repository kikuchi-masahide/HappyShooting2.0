#pragma once
#include "../Engine/Component.h"

class MyselfMediatorComponent;

/// <summary>
/// ���@�̌��N���(�ʏ�C�������C�r���r����...)�Ƃ���ɂ��ς��ʒu�X�V�̎d���C�`�惿�C�G�Ƃ̓����蔻����Ǘ�
/// </summary>
class MyselfConditionBase :
    public Component
{
public:
    MyselfConditionBase(GameObjectHandle handle, ComponentHandle<MyselfMediatorComponent> mediator);
    virtual ~MyselfConditionBase();
    /// <summary>
    /// �ʒu�C�`�惿�̍X�V���s���D
    /// </summary>
    virtual void Update() override = 0;
    /// <summary>
    /// �����蔻��Ŏ��@���_���[�W��H�炤��mediator����Ăяo����C
    /// �e�������������̏����ɉ����āC
    /// ���������e�̍U���͂�����_���[�W���v�Z����
    /// (����IsInvincible() == false�Ȃ�΂��̊֐��͌Ă΂�邱�Ƃ͂Ȃ�)
    /// </summary>
    /// <param name="attack">�G�e�U����</param>
    /// <returns>���_���[�W</returns>
    virtual unsigned int GetDamaged(unsigned int attack) = 0;
    /// <summary>
    /// �����@���_���[�W������Ȃ���ԂȂ��true��Ԃ�
    /// </summary>
    virtual bool IsInvincible() = 0;
protected:
    ComponentHandle<MyselfMediatorComponent> mediator_;
};


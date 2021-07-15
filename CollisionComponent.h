#pragma once
#include "Component.h"
#include "CollisionManager.h"

/// <summary>
/// �X�̃I�u�W�F�N�g�̓����蔻��
/// </summary>
class CollisionComponent :
    public Component
{
public:
    CollisionComponent(GameObjectHandle handle, int upd_priority, unsigned int tag, unsigned int damage);
    virtual ~CollisionComponent();
    /// ���g�̃^�O
    const unsigned int tag_;
    unsigned int GetDamage();
    /// <summary>
    /// CollisionManager�Ɏ��g�̎��􉽐}�`��ǉ�����
    /// (�P���ȃR�s�[�Ƃ��Ēǉ�����̂ŁC���W�̍X�V�͂��ׂďI��点�Ă����K�v������)
    /// </summary>
    virtual void Update() = 0;
    /// <summary>
    /// CheckHitComponent���s���C����set�ɏՓ˂����SCollisionComponent���[�߂���
    /// </summary>
    std::set<ComponentHandle<CollisionComponent>> hit_comps_;
    /// <summary>
    /// CollisionComponent�ƏՓ˂����ۂ̏���
    /// CollisionManager��TraverseAll()�����Ă���Œ��ɌĂяo�����
    /// </summary>
    /// <param name="hit_comps">�Փ˂����SCollisionComponent</param>
    virtual void CheckHitComponent() = 0;
protected:
    unsigned int damage_;
};


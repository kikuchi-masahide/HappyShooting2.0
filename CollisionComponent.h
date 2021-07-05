#pragma once
#include "Component.h"

/// <summary>
/// �X�̃I�u�W�F�N�g�̓����蔻��
/// </summary>
class CollisionComponent :
    public Component
{
public:
    CollisionComponent(int upd_priority, unsigned int tag, unsigned int damage);
    virtual ~CollisionComponent();
    /// ���g�̃^�O
    const unsigned int tag_;
    unsigned int GetDamage();
    /// <summary>
    /// �O�t���[���̍X�V���ʏՓ˂���component�S��
    /// </summary>
    std::vector<ComponentHandle<CollisionComponent>> hit_comps;
    virtual void Update() = 0;
protected:
    unsigned int damage_;
};


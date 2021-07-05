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
    CollisionComponent(int upd_priority, unsigned int tag, unsigned int damage);
    virtual ~CollisionComponent();
    /// ���g�̃^�O
    const unsigned int tag_;
    unsigned int GetDamage();
    /// <summary>
    /// �O�t���[���̍X�V���ʏՓ˂���component�S��
    /// </summary>
    std::vector<ComponentHandle<CollisionComponent>> hit_comps_;
    virtual void Update() = 0;
    /// <summary>
    /// CollisionManager�Ɏ��g�̎��􉽐}�`��ǉ�����
    /// CollisionManager::AddCollisionComponent�Ŏ��g��o�^����ƁC���̊֐���CollisionManager�̓����蔻�蒼�O�ɌĂяo�����C
    /// </summary>
    /// <param name="manager">���̃R���|�[�l���g���o�^���ꂽCollisionManager</param>
    virtual void AddGeometryToManager(CollisionManager& manager) = 0;
protected:
    unsigned int damage_;
};


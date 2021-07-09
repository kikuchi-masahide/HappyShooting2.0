#pragma once
#include "Component.h"

#include "GameObjectHandle.h"

class MainScene;

//�G�@�p�̗͊Ǘ��R���|�[�l���g
//0�����ɂȂ�ƃI�u�W�F�N�g�����ł����C���ŃG�t�F�N�g��ǉ�����
class EnemyHealthComponent :
    public Component
{
public:
    /// <param name="scene">���ŃI�u�W�F�N�g�ǉ��p�V�[���|�C���^</param>
    /// <param name="object">�e�I�u�W�F�N�g</param>
    /// <param name="health0">�J�n���̗�</param>
    EnemyHealthComponent(MainScene* scene, GameObjectHandle object, double health0);
    ~EnemyHealthComponent();
    /// <summary>
    /// �_���[�W��^����
    /// ���CollisionComponent::CheckHitComponent����Ăяo�����
    /// </summary>
    /// <returns>���ۂɋ������_���[�W(�̗�100��200�_���̒e�𓖂Ă���Ǝ��_���[�W��100)</returns>
    double Damage(double damage);
    /// <summary>
    /// �̗̓`�F�b�N
    /// </summary>
    void Update() override;
private:
    double health_;
    GameObjectHandle object_;
    MainScene* scene_;
};


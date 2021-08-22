#pragma once
#include "Component.h"

#include "GameObjectHandle.h"

class LayerManager;

//TODO:(���̃R���|�[�l���g�Ȃ�ō�����񂾂���...?)
//�G�@�p�̗͊Ǘ��R���|�[�l���g
//0�����ɂȂ�ƃI�u�W�F�N�g�����ł����C���ŃG�t�F�N�g��ǉ�����
class EnemyHealthComponent :
    public Component
{
public:
    /// <param name="scene">���ŃI�u�W�F�N�g�ǉ��p�V�[���|�C���^</param>
    /// <param name="object">�e�I�u�W�F�N�g</param>
    /// <param name="health0">�J�n���̗�</param>
    EnemyHealthComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer_manager, double health0);
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
    /// <summary>
    /// �c��̗̑͂��C�S�̗͂ɐ�߂銄����Ԃ�
    /// </summary>
    double GetHealthRate();
private:
    double all_health_;
    double health_;
    boost::shared_ptr<LayerManager> layer_manager_;
};


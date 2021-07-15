#pragma once
#include "CollisionComponent.h"

#include "GameObject.h"

class MainScene;

//���@�e�C�G�@�e�p�����蔻��
class BulletCollisionComponent :
    public CollisionComponent
{
public:
    /// <param name="mytag">�����̃^�O</param>
    /// <param name="enemytag">�������_���[�W��^����Ώۂ̃^�O</param>
    /// <param name="damage">�^������_���[�W�l</param>
    /// <param name="radius">�~�̔��a[px]</param>
    /// <param name="double_suicide">�Ώۂɓ���������I�u�W�F�N�g���Ǝ��ʂ��ǂ���</param>
    BulletCollisionComponent(GameObjectHandle obj, MainScene* scene, int upd_priority, unsigned int mytag, unsigned int enemytag, unsigned int damage, double radius, bool double_suicide = true);
    ~BulletCollisionComponent();
    void Update();
    void CheckHitComponent();
private:
    unsigned int enemy_tag_;
    double radius_;
    bool double_suicide_;
    MainScene* scene_;
};


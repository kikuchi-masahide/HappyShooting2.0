#pragma once
#include "../Engine/Component.h"

class LayerManager;
class CollisionManager;
class DrawNormalBulletComponent;
class NormalBulletCollisionComponent;

//Boss2State2�̒e�́A�����ʒu�ȊO�̏������E�X�V���s��
class Boss2State2Bullet :
    public Component
{
public:
    Boss2State2Bullet(GameObjectHandle obj, double deg, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col);
    ~Boss2State2Bullet();
    void Update() override;
private:
    //�ǂ̕����ɔ��ł�����
    double deg_;
    //���݂̑��x��Βl
    double abs_v_;
    int time_;
    ComponentHandle<DrawNormalBulletComponent> draw_;
    ComponentHandle<NormalBulletCollisionComponent> col_;
    //�����x��Βl(���x��-abs_g_��t�Ō���������)
    static const double abs_g_;
    //������Βl
    static const double abs_v0_;
    //���x��Βl�̍ŏ�
    static const double abs_v_min_;
    //�e�̔��a
    static const double radius_;
    //��tick�̊ԓ����蔻����������S�s�����ŕ`�悷�邩
    static const int lifetime_;
    //��tick�Ń�:1->0�ŏ������邩
    static const int fadeout_;
};


#pragma once
#include "../Engine/Component.h"

class LayerManager;
class CollisionManager;
class DrawNormalBulletComponent;
class NormalBulletCollisionComponent;

/// <summary>
/// Boss2State0�́A�ł������e���琶�܂�鏬�����̂̏������A�X�V
/// �������A�ʒu�̏����������͂ł�����������s��
/// </summary>
class Boss2State0BulletSmall :
    public Component
{
public:
    Boss2State0BulletSmall(GameObjectHandle obj, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col);
    ~Boss2State0BulletSmall();
    void Update() override;
private:
    //y�������̉����x
    static const double g_;
    //��tick�̊ԓ����蔻��������������邩
    static const int whole_duration_;
    //�����蔻���������I�u�W�F�N�g�����ɉ�tick�����邩
    static const int fadeout_period_;
    //�e�̔��a
    static const double radius_;
    //y�������̑��x�A�����x
    double v_;
    double a_;
    int time_;
    ComponentHandle<DrawNormalBulletComponent> draw_;
    ComponentHandle<NormalBulletCollisionComponent> col_;
};


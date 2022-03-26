#pragma once
#include "../Engine/Component.h"

#include "../Engine/Math/Math.h"

class LayerManager;
class CollisionManager;
class Boss2State3BulletColComponent;
class DrawNormalBulletComponent;

//�t�s�Đ��Ɋւ���L�q�́AMyBulletComponent�Q��
class Boss2State3Bullet :
    public Component
{
public:
    Boss2State3Bullet(GameObjectHandle obj, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col);
    ~Boss2State3Bullet();
    void Update() override;
    void SetProgradePlay();
    void SetRetrogradePlay(unsigned int speed);
private:
    //�e�̔��a
    static const double radius_;
    //�e�̑��x
    static const double v_;
    static const int grace_time_;
    int speed_;
    int time_;
    int last_time_in_stage_;
    ComponentHandle<Boss2State3BulletColComponent> collision_;
    ComponentHandle<DrawNormalBulletComponent> draw_;
    //�n�߂̈ʒu(�ʒu�����ɕK�v)
    MatVec::Vector2 pos0_;
    //����t����ʒu�����߂�
    MatVec::Vector2 SolvePosWhen(int time);
    //����t���瓧���x�����߂�
    double SolveAlphaWhen(int time);
};


#pragma once
#include "CollisionComponent.h"

#include "GameObject.h"
#include "CircleGeometry.h"

class MainScene;

//���@�e�p�̓����蔻��R���|�[�l���g
class MyBulletCollisionComponent :
    public CollisionComponent
{
public:
    /// <param name="damage">�^������_���[�W�l</param>
    /// <param name="radius">�~�̔��a[px]</param>
    /// <param name="double_suicide">�Ώۂɓ���������I�u�W�F�N�g���Ǝ��ʂ��ǂ���</param>
    MyBulletCollisionComponent(GameObjectHandle obj, boost::shared_ptr<CollisionManager> manager, unsigned int damage, double radius);
    ~MyBulletCollisionComponent();
    void Update();
    void CheckHitComponent();
private:
    double radius_;
    CircleGeometry circle_;
};


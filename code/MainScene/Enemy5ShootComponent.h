#pragma once
#include "../Engine/Component.h"

#include "../Engine/Math/Math.h"

class LayerManager;
class CollisionManager;

/// <summary>
/// ���@�_���e�����Ԋu�Ō��R���|�[�l���g
/// </summary>
class Enemy5ShootComponent :
    public Component
{
public:
    /// <param name="myself">���@�I�u�W�F�N�g</param>
    /// <param name="radius">�e�̔��a</param>
    /// <param name="speed">�e�̑��x</param>
    /// <param name="period">���Ԋu(�J�E���^�[���񕉂���period�Ŋ���؂��^�C�~���O�Ō���)</param>
    /// <param name="counter0">�J�E���^�̏����l(�ŏ���Update()�ł̃J�E���^�̒l������)</param>
    /// <param name="attack">�U����</param>
    /// <param name="edge_rgb">�e�̉��̐F(�ȗ�����)</param>
    /// <param name="edge_alpha">�e�̉��̃�(�ȗ���1)</param>
    Enemy5ShootComponent(GameObjectHandle handle, int priority, GameObjectHandle myself, double radius, double speed, unsigned int period, int counter0, unsigned int attack, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<CollisionManager> collision_manager, MatVec::Vector3 edge_rgb = MatVec::Vector3(1.0, 0.0, 0.0), double edge_alpha = 1.0);
    ~Enemy5ShootComponent();
    void Update() override;
private:
    GameObjectHandle myself_;
    unsigned int attack_;
    unsigned int period_;
    int counter_;
    double speed_;
    double radius_;
    boost::shared_ptr<LayerManager> layer_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    MatVec::Vector3 edge_rgb_;
    double edge_alpha_;
};


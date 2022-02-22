#pragma once
#include "../Engine/Component.h"

class LayerManager;
class ScoreManager;
class EnemyWaveManager;
class CollisionManager;
class DrawAnimationComponent;
class EnemyHealthComponent;

class Enemy6MediatorComponent :
    public Component
{
public:
    /// <summary>
    /// time,x0,y0,dx,life�͐e��������p�����
    /// </summary>
    /// <param name="time">�J�E���^�[(0�X�^�[�g)</param>
    /// <param name="x0">�ŏ��̈ʒu</param>
    /// <param name="y0">�ŏ��̈ʒu</param>
    /// <param name="dx">��tick��x�ړ���</param>
    /// <param name="life">�̗�</param>
    Enemy6MediatorComponent(GameObjectHandle _handle, int time, double x0, double y0, double dx, int life,
        boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager,
        boost::shared_ptr<EnemyWaveManager> enemywave_manager,
        boost::shared_ptr<CollisionManager> collision_manager);
    ~Enemy6MediatorComponent();
    void Update() override;
    //���C�t�����l
    static constexpr int life0_ = 3000;
private:
    //��������
    void Clone();
    ComponentHandle<DrawAnimationComponent> animation_;
    ComponentHandle<EnemyHealthComponent> health_;
    //time�����̒l�ɂȂ�Update�܂Ŏ��s����
    constexpr static int lifetime_ = 60*20 - 1;
    //���̎��Ԃ��Ƃɕ��􂷂�
    constexpr static int clone_cycle_ = 60 * 4;
    //y�ω���
    static constexpr double dy_ = -0.5;
    //1tick������̈ړ���
    double dx_;
    int life_;
    int time_;
    boost::shared_ptr<LayerManager> layer_manager_;
    boost::shared_ptr<ScoreManager> score_manager_;
    boost::shared_ptr<EnemyWaveManager> enemywave_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    //���ɍۂ̍U��
    void DeathAttack();
};


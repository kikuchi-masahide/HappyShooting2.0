#pragma once
#include "Boss2StateBase.h"

class LayerManager;
class ScoreManager;
class CollisionManager;
class Boss2MediatorComponent;
class EnemyWaveManager;

class Boss2State1 :
    public Boss2StateBase
{
public:
    Boss2State1(ComponentHandle<Boss2MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager);
    ~Boss2State1();
    void Update() override;
    bool IsCollisionActive() override;
    bool IsInvincible() override;
private:
    int time_;
    //start_shooting_time_ <= time_ < end_shootin_time_�̊Ԓe������
    static const int start_shooting_time_;
    static const int end_shooting_time_;
    //���̎ˌ��ŉ��e���o����
    static const int bullet_num_per_;
    //�ˌ��Ǝˌ��̊Ԃ���tick��
    static const int shoot_period_;
    //state_duration_ tick�̊Ԃ��̃X�e�[�g���ێ�
    static const int state_duration_;
    //bullet_num_per_�̒e��ǉ�
    void Shoot();
};


#pragma once
#include "Boss1StateBase.h"

//Boss1�̓���U��1��(�����C�^���C�E������傫�Ȓe���|�[���Əo��)
class Boss1State1 :
    public Boss1StateBase
{
public:
    Boss1State1(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager);
    ~Boss1State1();
    void Update() override;
    bool IsCollisionActive() override;
    bool IsInvincible() override;
private:
    //Update()�̎��s�񐔃J�E���g(1��ڂ�Update���s�̊�counter_��0�ł���)
    unsigned int counter_;
    //1��ڂ̒e�ł��o����counter_�����ɂȂ����炩(�^������)
    static constexpr unsigned int launch_counter_first_ = 50*60/25-1;
    //2��ڂ̒e�ł��o����counter_�����ɂȂ����炩(�����C�E������)
    static constexpr unsigned int launch_counter_second_ = 150*60/25-1;
    //3��ڂ̒e�ł��o����counter_�����ɂȂ����炩(�����C�^���C�E������)
    static constexpr unsigned int launch_counter_third_ = 300*60/25-1;
    //�e�����������ۂ�x���W
    static constexpr double popup_leftx_ = -150.0;
    static constexpr double popup_centerx_ = 0.0;
    static constexpr double popup_rightx_ = 150.0;
    //counter_�����ɂȂ�����NormalState�ɖ߂邩
    static constexpr unsigned int terminal_counter_ = 450*60/25-1;
    //����x���W�ŏ㉺�^������CMasterBullet��ǉ�����
    void AddMasterBullet(double x);
};


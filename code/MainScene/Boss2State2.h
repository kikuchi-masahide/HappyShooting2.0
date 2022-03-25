#pragma once
#include "Boss2StateBase.h"

#include "../Engine/Math/Math.h"

//Boss2State2�ɂ�����A�{�X�̍s���ʒu�Ƃ��̃^�C�~���O
struct Boss2State2TimeTable {
public:
    int time_;
    MatVec::Vector2 pos_;
    Boss2State2TimeTable(int t, MatVec::Vector2 p) :time_(t), pos_(p) {};
};

//�{�X���ǂɂԂ����Ă��ăX�e�[�W������`����ėh��ĂԂ������Ƃ�����e���Ԃ�`���ďo�Ă�����
class Boss2State2 :
    public Boss2StateBase
{
public:
    Boss2State2(ComponentHandle<Boss2MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager);
    ~Boss2State2();
    void Update() override;
    bool IsCollisionActive() override;
    bool IsInvincible() override;
    //timetable_[n].time_�̂Ƃ��\���ʒu��timetable_[n].pos_�ł���悤�Ɉړ����� �Ԃ͐��`�⊮
    static const Boss2State2TimeTable timetable_[16];
private:
    int time_;
    //�l���ɒe���΂�܂�
    void Shoot();
    //����state���ێ����鎞��
    static const int state_duration_;
    //�J�x�ɂԂ������Ƃ����e����o���邩
    static const int bullet_num_;
};


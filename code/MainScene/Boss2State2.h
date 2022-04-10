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
    //timetable_[n].time_�̂Ƃ��\���ʒu��timetable_[n].pos_�ł���悤�Ɉړ����� �Ԃ͐��`�⊮
    //(Layer����Q�Ƃ��邽�߁Apublic�ɒu���Ă���)
    //TODO:�ݒ���O���t�@�C������ǂݍ��ނ悤�ɂ����肷��΁ALayer���炱�̃N���X���Q�Ƃ��邱�Ƃ�������ł����ǂ�...
    static const Boss2State2TimeTable timetable_[16];
    //����state���ێ����鎞��
    static const int state_duration_;
private:
    int time_;
    //�l���ɒe���΂�܂�
    void Shoot();
    //�J�x�ɂԂ������Ƃ����e����o���邩
    static const int bullet_num_;
};


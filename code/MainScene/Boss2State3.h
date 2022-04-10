#pragma once
#include "Boss2StateBase.h"

class Boss2State3Bullet;

class Boss2State3 :
    public Boss2StateBase
{
public:
    Boss2State3(ComponentHandle<Boss2MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager);
    ~Boss2State3();
    void Update() override;
private:
    int time_;
    //�����̌Q�𐶐����邩
    int wave_num_;
    //�ŏ��ɒe���o���Ƃ��́A���܊p�`�̔��a
    static const double r0_;
    //���Q�́A��tick�Ɉ�̃y�[�X�Œe�𐶐����邩(�ł����60�̖񐔂ł����Ăق���)
    static const int bullet_gen_freq_;
    std::vector<ComponentHandle<Boss2State3Bullet>> bullets_;
    //��n���́Am�Q�ڂ̒e�𐶐�����(�v5��)
    void GenerateBullets(int n, int m);
    //���@�E���@�e�E�������������������ׂď��s�Đ�������(���łɎ���ł�n���h�����폜)
    void SetProgradePlay();
    //���@�E���@�e�E�������������������ׂċt�s�Đ�������
    void SetRetrogradePlay(unsigned int speed);
};


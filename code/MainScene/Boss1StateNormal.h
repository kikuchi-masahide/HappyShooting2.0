#pragma once
#include "Boss1StateBase.h"

#include "Math.h"
#include "../Engine/GameObject.h"

/// <summary>
/// �c��񂾎O�p�`�̒ʏ�e�����������郂�[�h
/// </summary>
class Boss1StateNormal :
    public Boss1StateBase
{
public:
    /// <param name="next_state">���̃��[�h���I���������ƁCBoss1State1,3�̂ǂ���ɑJ�ڂ��邩</param>
    Boss1StateNormal(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, unsigned int next_state);
    ~Boss1StateNormal();
    void Update() override;
private:
    int counter_;
    //�e��������
    double deg_;
    //��Boss1State1~3�̂ǂ���ɑJ�ڂ��邩
    unsigned int next_state_;
    static constexpr double delta_deg_ = PI/120;
    //���̒e������
    static constexpr int bullet_num_ = 96;
    //��tick�����ɒe�������D
    static constexpr int bullet_period_ = 30;
    //���̃��[�h����tick������
    static constexpr int mode_period_ = 480;
    //�e��
    static constexpr double bullet_speed_ = 4.0;
};


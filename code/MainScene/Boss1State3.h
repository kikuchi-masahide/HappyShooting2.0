#pragma once
#include "Boss1StateBase.h"

#include "../Engine/Math/Math.h"

class MyselfPosAdjustComponent;

class Boss1State3 :
    public Boss1StateBase
{
public:
	Boss1State3(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager);
	~Boss1State3();
	void Update() override;
	bool IsCollisionActive() override;
	bool IsInvincible() override;
private:
	//�͂��߂Ă�Update()���s���Ccounter_initial_�ɂЂƂ���
	int counter_;
	static constexpr int counter_initial_ = -60;
	//counter_�����̒l�ɂȂ�Update�܂Ŏ��s����
	static constexpr int whole_period_ = 780 - 1;
	//���@�_���̒e�̍��E�Ɍ��e�́C���@�_���e�Ƃ̊p�x�̍�
	static constexpr double ball_angle_dif_ = PI / 6;
	//�e�̑���
	static constexpr double ball_speed_ = 10.0;
	//�e�̔��a
	static constexpr double ball_size_ = 40.0;
	//���񎩋@�_���e������
	static constexpr unsigned int launch_repeat_time_ = 12;
	//���@�_���e�C���̍��E�̒e�̌v3��ǉ�����
	void AddBullet();
	//���@�ړ��̈�k���C�Ċg��ɉ�tick�����邩
	static constexpr unsigned int shrink_period_ = 240;
	//���̊p�x�܂ňړ��̈���X����
	static constexpr double max_rotate_angle_ = -PI / 3;
	//�ړ��̈�����{�Ɋg�傷�邩
	static constexpr double max_expand_ratio_ = 0.4;
	ComponentHandle<MyselfPosAdjustComponent> pos_adjust_[4];
};


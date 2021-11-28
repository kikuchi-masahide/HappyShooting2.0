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
	//‚Í‚¶‚ß‚Ä‚ÌUpdate()ÀsCcounter_initial_‚É‚Ğ‚Æ‚µ‚¢
	int counter_;
	static constexpr int counter_initial_ = -60;
	//counter_‚ª‚±‚Ì’l‚É‚È‚éUpdate‚Ü‚ÅÀs‚·‚é
	static constexpr int whole_period_ = 780 - 1;
	//©‹@‘_‚¢‚Ì’e‚Ì¶‰E‚ÉŒ‚‚Â’e‚ÌC©‹@‘_‚¢’e‚Æ‚ÌŠp“x‚Ì·
	static constexpr double ball_angle_dif_ = PI / 6;
	//’e‚Ì‘¬‚³
	static constexpr double ball_speed_ = 10.0;
	//’e‚Ì”¼Œa
	static constexpr double ball_size_ = 40.0;
	//‰½‰ñ©‹@‘_‚¢’e‚ğŒ‚‚Â‚©
	static constexpr unsigned int launch_repeat_time_ = 12;
	//©‹@‘_‚¢’eC‚»‚Ì¶‰E‚Ì’e‚ÌŒv3‚Â‚ğ’Ç‰Á‚·‚é
	void AddBullet();
	//©‹@ˆÚ“®—Ìˆæk¬CÄŠg‘å‚É‰½tick‚©‚¯‚é‚©
	static constexpr unsigned int shrink_period_ = 240;
	//‚±‚ÌŠp“x‚Ü‚ÅˆÚ“®—Ìˆæ‚ğŒX‚¯‚é
	static constexpr double max_rotate_angle_ = -PI / 3;
	//ˆÚ“®—Ìˆæ‚ğ‰½”{‚ÉŠg‘å‚·‚é‚©
	static constexpr double max_expand_ratio_ = 0.4;
	ComponentHandle<MyselfPosAdjustComponent> pos_adjust_[4];
};


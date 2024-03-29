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
	//はじめてのUpdate()実行時，counter_initial_にひとしい
	int counter_;
	static constexpr int counter_initial_ = -60;
	//counter_がこの値になるUpdateまで実行する
	static constexpr int whole_period_ = 780 - 1;
	//自機狙いの弾の左右に撃つ弾の，自機狙い弾との角度の差
	static constexpr double ball_angle_dif_ = PI / 6;
	//弾の速さ
	static constexpr double ball_speed_ = 10.0;
	//弾の半径
	static constexpr double ball_size_ = 40.0;
	//何回自機狙い弾を撃つか
	static constexpr unsigned int launch_repeat_time_ = 12;
	//自機狙い弾，その左右の弾の計3つを追加する
	void AddBullet();
	//自機移動領域縮小，再拡大に何tickかけるか
	static constexpr unsigned int shrink_period_ = 240;
	//この角度まで移動領域を傾ける
	static constexpr double max_rotate_angle_ = -PI / 3;
	//移動領域を何倍に拡大するか
	static constexpr double max_expand_ratio_ = 0.4;
	ComponentHandle<MyselfPosAdjustComponent> pos_adjust_[4];
};


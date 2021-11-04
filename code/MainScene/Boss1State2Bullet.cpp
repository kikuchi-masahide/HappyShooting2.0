#include "Boss1State2Bullet.h"

#include "DrawNormalBulletComponent.h"
#include "NormalBulletCollisionComponent.h"

Boss1State2Bullet::Boss1State2Bullet(GameObjectHandle handle, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<LayerManager> layer_manager)
	:Component(handle),
	counter_(0),collision_manager_(collision_manager)
{
	if (!static_init_flag_) {
		engine_ = std::mt19937(seed_gen_());
		dist_ = std::uniform_real_distribution<>(0.0, 1.0);
	}
	draw_component_ = mObj->AddOutputComponent<DrawNormalBulletComponent>(layer_manager, size_, MatVec::Vector3(1.0, 0.0, 0.0), 0.0, -10.0);
	//最初の速度は[-1.0,1.0)の乱数とする
	dx_ = dist_(engine_)*2-1.0;
	dy_ = dist_(engine_)*2-1.0;
}

void Boss1State2Bullet::Update()
{
	if (counter_ < visualization_period_)
	{
		draw_component_->edge_alpha_ = (double)counter_ / visualization_period_;
		//このtickで実体化が終わる
		if (counter_ == visualization_period_ - 1)
		{
			collision_component_ = mObj->AddUpdateComponent<NormalBulletCollisionComponent>(size_, 100.0, collision_manager_);
		}
	}
	else if (counter_ < visualization_period_ + freemove_period_)
	{
		//TODO:移動ルーチンの改善(思ってたより早い)
		auto pos = mObj->GetPosition();
		dx_ += (dist_(engine_) - 0.5) * 0.2;
		if (dx_ > 2.0 || pos(0) <= -300.0)
		{
			dx_ = 0.3;
		}
		if (dx_ < -2.0 || pos(0) >= 300.0)
		{
			dx_ = -0.3;
		}
		dy_ += (dist_(engine_) - 0.5) * 0.2;
		if (dy_ > 2.0 || pos(0) <= -450.0)
		{
			dy_ = 0.3;
		}
		if (dy_ < -2.0 || pos(0) >= 450.0)
		{
			dy_ = -0.3;
		}
		pos(0) += dx_;
		pos(1) += dy_;
		mObj->SetPosition(pos);
		if (counter_ == visualization_period_ + freemove_period_ - 1)
		{
			collision_component_->SetDeleteFlag();
		}
	}
	else {
		draw_component_->edge_alpha_ = 1.0 - (double)(counter_ - visualization_period_ - freemove_period_) / unvisualization_period_;
		if (counter_ == visualization_period_ + freemove_period_ - 1)
		{
			mObj->SetDeleteFlag();
		}
	}
	counter_++;

}

Boss1State2Bullet::~Boss1State2Bullet()
{
}

std::random_device Boss1State2Bullet::seed_gen_;
std::mt19937 Boss1State2Bullet::engine_;
std::uniform_real_distribution<> Boss1State2Bullet::dist_;
bool Boss1State2Bullet::static_init_flag_ = false;
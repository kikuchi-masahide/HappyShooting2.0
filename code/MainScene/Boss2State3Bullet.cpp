#include "Boss2State3Bullet.h"

#include "Boss2State3BulletColComponent.h"
#include "DrawNormalBulletComponent.h"

Boss2State3Bullet::Boss2State3Bullet(GameObjectHandle obj, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col)
	:Component(obj),
	last_time_in_stage_(-1),speed_(1),time_(-1)
{
	collision_ = mObj->AddUpdateComponent<Boss2State3BulletColComponent>(col);
	draw_ = mObj->AddOutputComponent<DrawNormalBulletComponent>(
		layer, radius_, MatVec::Vector3(1.0, 0.0, 0.0), 1.0, 10.0);
	draw_->edge_alpha_ = 0.0;
	pos0_ = mObj->GetPosition();
}

Boss2State3Bullet::~Boss2State3Bullet()
{
}

void Boss2State3Bullet::Update()
{
	time_ += speed_;
	auto pos = SolvePosWhen(time_);
	mObj->SetPosition(pos);
	if (speed_ == 1)
	{
		if (abs(pos(0)) <= 300.0 + radius_ && abs(pos(1)) <= 450.0 + radius_ && collision_->active_)
		{
			last_time_in_stage_ = max(last_time_in_stage_, time_);
			draw_->edge_alpha_ = SolveAlphaWhen(time_);
		}
		else {
			collision_->active_ = false;
			draw_->edge_alpha_ = 0.0;
		}
		if (time_ >= last_time_in_stage_ + grace_time_)
		{
			mObj->SetDeleteFlag();
		}
	}
	else {
		if (time_ <= last_time_in_stage_)
		{
			draw_->edge_alpha_ = SolveAlphaWhen(time_);
			last_time_in_stage_ = time_;
		}
		else {
			draw_->edge_alpha_ = 0.0;
		}
	}
	if (time_ + speed_ < 0)
	{
		mObj->SetDeleteFlag();
	}
}

void Boss2State3Bullet::SetProgradePlay()
{
	speed_ = 1;
	if (time_ <= last_time_in_stage_)
	{
		collision_->active_ = true;
	}
}

void Boss2State3Bullet::SetRetrogradePlay(unsigned int speed)
{
	if (speed != 0)
	{
		speed_ = -(int)speed;
		collision_->active_ = false;
	}
}

MatVec::Vector2 Boss2State3Bullet::SolvePosWhen(int time)
{
	//ŽÀ‘Ì‰»‚Ì‚Æ‚«
	if (time < 60)
	{
		return pos0_;
	}
	//ˆÚ“®‚·‚é‚Æ‚«
	return pos0_ + v_ * (time-60) * pos0_ / pos0_.Norm();
}

double Boss2State3Bullet::SolveAlphaWhen(int time)
{
	if (time < 60)
	{
		return min((double)time / 20,1.0);
	}
	else {
		return 1.0;
	}
}

const double Boss2State3Bullet::radius_ = 10.0;
const double Boss2State3Bullet::v_ = 2.5;
const int Boss2State3Bullet::grace_time_ = 360;

#include "Boss2State2Bullet.h"

#include "DrawNormalBulletComponent.h"
#include "NormalBulletCollisionComponent.h"

Boss2State2Bullet::Boss2State2Bullet(GameObjectHandle obj, double deg, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col)
	:Component(obj),
	deg_(deg),time_(0),abs_v_(abs_v0_)
{
	draw_ = mObj->AddOutputComponent<DrawNormalBulletComponent>(layer, radius_, MatVec::Vector3(1.0, 0.0, 0.0), 1.0, -10.0);
	col_ = mObj->AddUpdateComponent<NormalBulletCollisionComponent>(radius_, 100, col);
}

Boss2State2Bullet::~Boss2State2Bullet()
{
}

void Boss2State2Bullet::Update()
{
	auto pos = mObj->GetPosition();
	pos += abs_v_ / 60 * MatVec::Vector2(cos(deg_),sin(deg_));
	mObj->SetPosition(pos);
	if (abs(pos(0)) > 300 + radius_ || abs(pos(1)) > 450 + radius_)
	{
		mObj->SetDeleteFlag();
	}
	abs_v_ -= abs_g_ / 60;
	if (abs_v_ < abs_v_min_)
	{
		abs_v_ = abs_v_min_;
	}
	if (time_ >= lifetime_)
	{
		draw_->edge_alpha_ = 1.0 - (double)(time_ - lifetime_) / fadeout_;
	}
	time_++;
	if (time_ == lifetime_)
	{
		col_->SetDeleteFlag();
	}
	if (time_ == lifetime_ + fadeout_)
	{
		mObj->SetDeleteFlag();
	}
}

const double Boss2State2Bullet::abs_g_ = -100;
const double Boss2State2Bullet::abs_v0_ = 100.0;
const double Boss2State2Bullet::abs_v_min_ = 5.0;
const double Boss2State2Bullet::radius_ = 20.0;
const int Boss2State2Bullet::lifetime_ = 120;
const int Boss2State2Bullet::fadeout_ = 60;

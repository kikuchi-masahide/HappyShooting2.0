#include "Boss2State0BulletSmall.h"

#include "DrawNormalBulletComponent.h"
#include "NormalBulletCollisionComponent.h"

Boss2State0BulletSmall::Boss2State0BulletSmall(GameObjectHandle obj, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col)
	:Component(obj),
	v_(0.0),a_(0.0),time_(0)
{
	draw_ = mObj->AddOutputComponent<DrawNormalBulletComponent>(layer, radius_, MatVec::Vector3(1.0, 0.5, 0.0), 1.0, -10.0);
	col_ = mObj->AddUpdateComponent<NormalBulletCollisionComponent>(radius_, 100, col);
}

Boss2State0BulletSmall::~Boss2State0BulletSmall()
{
}

void Boss2State0BulletSmall::Update()
{
	auto pos = mObj->GetPosition();
	pos(1) += v_ / 60;
	mObj->SetPosition(pos);
	if (time_ >= whole_duration_)
	{
		double t = time_ - whole_duration_;
		draw_->edge_alpha_ = 1.0 - t / fadeout_period_;
	}
	if (time_ < whole_duration_) {
		v_ += a_ / 60;
		a_ += g_ / 60;
	}
	time_++;
	if (time_ == whole_duration_)
	{
		col_->SetDeleteFlag();
	}
	else if (time_ == whole_duration_ + fadeout_period_)
	{
		mObj->SetDeleteFlag();
	}
}

const double Boss2State0BulletSmall::g_ = -9.8 * 25;
const int Boss2State0BulletSmall::whole_duration_ = 120;
const int Boss2State0BulletSmall::fadeout_period_ = 30;
const double Boss2State0BulletSmall::radius_ = 10.0;


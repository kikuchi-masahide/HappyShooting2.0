#include "Boss2State1Bullet.h"

#include "DrawTextureComponent.h"
#include "Boss1BulletCollisionComponent.h"

Boss2State1Bullet::Boss2State1Bullet(GameObjectHandle obj, bool go_down, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col)
	:Component(obj),
	v_(0),go_down_(go_down)
{
	auto texture = mObj->AddOutputComponent<DrawTextureComponent>(layer, 19, -10.0);
	texture->width_ = 40;
	texture->height_ = 40;
	texture->alpha_ = 1.0;
	if (go_down_) {
		texture->angle_offset_ = -PI / 2;
	}
	else {
		texture->angle_offset_ = PI / 2;
	}
	mObj->AddUpdateComponent<Boss1BulletCollisionComponent>(col);
	//xÀ•W‚Íƒ‰ƒ“ƒ_ƒ€‚ÉŒˆ‚ß‚é
	//—”
	static std::random_device seed_gen;
	static std::mt19937 engine(seed_gen());
	//[-1,1)—”
	static std::uniform_real_distribution<> dist(-1.0, 1.0);
	double x = 300.0 * dist(engine);
	if (go_down_) {
		mObj->SetPosition(MatVec::Vector2(x, 450.0 + 20.0));
	}
	else {
		mObj->SetPosition(MatVec::Vector2(x, -450.0 - 20.0));
	}
}

Boss2State1Bullet::~Boss2State1Bullet()
{
}

void Boss2State1Bullet::Update()
{
	auto pos = mObj->GetPosition();
	pos(1) += v_ / 60;
	if (go_down_) {
		v_ -= abs_g_ / 60;
		if (abs(v_) > max_v_)
		{
			v_ = -max_v_;
		}
	}
	else {
		v_ += abs_g_ / 60;
		if (abs(v_) > max_v_)
		{
			v_ = max_v_;
		}
	}
	if (abs(v_) > max_v_)
	{
		if (go_down_) {
			v_ = -max_v_;
		}
		else {
			v_ = max_v_;
		}
	}
	mObj->SetPosition(pos);
	if (abs(pos(1)) > 450 + 20)
	{
		mObj->SetDeleteFlag();
	}
}

const double Boss2State1Bullet::abs_g_ = 240;
const double Boss2State1Bullet::max_v_ = 210;

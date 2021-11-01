#include "Boss1State1MasterBullet.h"

#include "../Engine/GameObject.h"
#include "DrawNormalBulletComponent.h"
#include "NormalBulletCollisionComponent.h"
#include "../Engine/Scene.h"
#include "AcceleratedMoveComponent.h"

Boss1State1MasterBullet::Boss1State1MasterBullet(GameObjectHandle handle, double startx, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager)
	:Component(handle),
	counter_(0),x_(startx),layer_manager_(layer_manager),score_manager_(score_manager),collision_manager_(collision_manager)
{
	mObj->SetPosition(MatVec::Vector2(startx,starty_));
	mObj->AddOutputComponent<DrawNormalBulletComponent>(layer_manager_, size_, MatVec::Vector3(1.0, 0.0, 0.0), 1.0, -10.0);
	mObj->AddUpdateComponent<NormalBulletCollisionComponent>(size_, 100, collision_manager_);
}

void Boss1State1MasterBullet::Update()
{
	//counter_‚ªt‚Ì‚Æ‚«‚ÌyÀ•Wy‚É‚Â‚¢‚ÄCendy_-y‚ª(terminal_counter_-t)^2‚É”ä—á‚·‚é‚æ‚¤‚É‚·‚é
	static double C = (endy_ - starty_) / (terminal_counter_ * terminal_counter_);
	double y = endy_ - C * (terminal_counter_ - counter_) * (terminal_counter_ - counter_);
	mObj->SetPosition(MatVec::Vector2(x_, y));
	if (counter_ == terminal_counter_)
	{
		AddSmallBullet();
		mObj->SetDeleteFlag();
	}
	counter_++;
}

Boss1State1MasterBullet::~Boss1State1MasterBullet()
{
}

void Boss1State1MasterBullet::AddSmallBullet()
{
	auto scene = mObj->mScene;
	auto pos = mObj->GetPosition();
	for (int n = 0; n < small_bullet_num_; n++)
	{
		auto bullet = scene->AddObject(MatVec::Vector2(), 1.0, 0.0);
		double deg = 2 * PI * n / small_bullet_num_;
		bullet->AddUpdateComponent<AcceleratedMoveComponent>(0, pos, MatVec::Vector2(cos(deg), sin(deg)) * small_bullet_v0_, MatVec::Vector2(0.0, small_bullet_ay_));
		bullet->AddOutputComponent<DrawNormalBulletComponent>(layer_manager_, small_bullet_size_, MatVec::Vector3(1.0, 0.0, 0.0), 1.0, -10.0);
		bullet->AddUpdateComponent<NormalBulletCollisionComponent>(small_bullet_size_, 100, collision_manager_);
	}
}

#include "Enemy8BulletComponent.h"

#include "DrawNormalBulletComponent.h"
#include "NormalBulletCollisionComponent.h"

Enemy8BulletComponent::Enemy8BulletComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, double angle, GameObjectHandle myself)
	:Component(handle),
	myself_(myself),angle_(angle),time_(0)
{
	mObj->AddOutputComponent<DrawNormalBulletComponent>(layer_manager, 5, MatVec::Vector3(1.0, 0.5, 0.0), 1.0, -10.0);
	mObj->AddUpdateComponent<NormalBulletCollisionComponent>(5, 100, collision_manager);
}

Enemy8BulletComponent::~Enemy8BulletComponent()
{
}

void Enemy8BulletComponent::Update()
{
	auto pos = mObj->GetPosition();
	//最初の0.5秒はシンプルに広がるだけ
	if (time_ < 30)
	{
		pos(0) += (30 - time_) * 2.0 / 24 * cos(angle_);
		pos(1) += (30 - time_) * 2.0 / 24 * sin(angle_);
	}
	//その後は自機狙い弾に切り替え
	else
	{
		//始めのtickではangle_を自機向きに
		if (time_ == 30)
		{
			auto posdif = myself_->GetPosition()-pos;
			angle_ = atan2(posdif(1), posdif(0));
		}
		pos += MatVec::Vector2(cos(angle_), sin(angle_)) * 3.5;
		//進んでいって画面外に出た
		if (abs(pos(0)) > 300+5 || abs(pos(1)) > 450+5)
		{
			mObj->SetDeleteFlag();
		}
	}
	mObj->SetPosition(pos);
	time_++;
}

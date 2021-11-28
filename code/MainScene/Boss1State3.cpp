#include "Boss1State3.h"

#include "Boss1MediatorComponent.h"
#include "Boss1StateNormal.h"
#include "EnemyWaveManager.h"
#include "../Engine/Scene.h"
#include "LinearMoveComponent.h"
#include "DrawNormalBulletComponent.h"
#include "NormalBulletCollisionComponent.h"

Boss1State3::Boss1State3(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager)
	:Boss1StateBase(mediator,layer_manager,score_manager,collision_manager,enemywave_manager),
	counter_(counter_initial_)
{
}

Boss1State3::~Boss1State3()
{
}

void Boss1State3::Update()
{
	//counter_が負の時は待機
	if (counter_ < 0)
	{
		counter_++;
		return;
	}
	//n秒+0,3,6,...,30tick(n=0,...,launch_repeat_time_-1)のタイミングで弾を撃つ
	if (counter_ < 60 * launch_repeat_time_) {
		int counter_mod_60 = counter_ % 60;
		if (counter_mod_60 % 3 == 0 && counter_mod_60 <= 30)
		{
			AddBullet();
		}
	}
	//このモード終了
	if (counter_ == whole_period_)
	{
		mediator_->ChangeState(DBG_NEW Boss1StateNormal(mediator_, layer_manager_, score_manager_, collision_manager_, enemywave_manager_, 1));
	}
	counter_++;
}

bool Boss1State3::IsCollisionActive()
{
	return true;
}

void Boss1State3::AddBullet()
{
	auto myself_pos = enemywave_manager_->GetMyselfHandle()->GetPosition();
	myself_pos -= mediator_->mObj->GetPosition();
	double theta0 = atan2(myself_pos(1), myself_pos(0)) - ball_angle_dif_;
	for (unsigned int n = 0; n < 3; n++)
	{
		//この方向に弾を飛ばす
		double theta = theta0 + ball_angle_dif_ * n;
		auto obj = mediator_->mObj->mScene->AddObject(mediator_->mObj->GetPosition(), 1.0, theta);
		obj->AddUpdateComponent<LinearMoveComponent>(MatVec::Vector2(cos(theta), sin(theta)) * ball_speed_, ball_size_);
		obj->AddOutputComponent<DrawNormalBulletComponent>(layer_manager_, ball_size_, MatVec::Vector3(1.0, 0.0, 0.0), 1.0, -10.0);
		obj->AddUpdateComponent<NormalBulletCollisionComponent>(ball_size_, 100.0, collision_manager_);
	}
}

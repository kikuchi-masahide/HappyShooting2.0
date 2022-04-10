#include "Boss2State1.h"

#include "Boss2Mediator.h"
#include "Boss2State2.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "Boss2State1Bullet.h"
#include "LayerManager.h"

Boss2State1::Boss2State1(ComponentHandle<Boss2MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager)
	:Boss2StateBase(mediator,layer_manager,score_manager,collision_manager,enemywave_manager),
	time_(0)
{
	layer_manager_->SwapLayer(3);
}

Boss2State1::~Boss2State1()
{
}

void Boss2State1::Update()
{
	if (time_ >= start_shooting_time_ && time_ < end_shooting_time_)
	{
		int t = time_ - start_shooting_time_;
		if (t % shoot_period_ == 0)
		{
			Shoot();
		}
	}
	time_++;
	if (time_ == state_duration_)
	{
		layer_manager_->SwapLayer(0);
		mediator_->ChangeState(boost::shared_ptr<Boss2State2>(DBG_NEW Boss2State2(
			mediator_, layer_manager_, score_manager_, collision_manager_, enemywave_manager_
		)));
	}
}

void Boss2State1::Shoot()
{
	auto scene = mediator_->mObj->mScene;
	for (int n = 0; n < bullet_num_per_;n++)
	{
		auto bullet = scene->AddObject(MatVec::Vector2(), 1.0, 0.0);
		bullet->AddUpdateComponent<Boss2State1Bullet>(true, layer_manager_, collision_manager_);
		bullet = scene->AddObject(MatVec::Vector2(), 1.0, 0.0);
		bullet->AddUpdateComponent<Boss2State1Bullet>(false, layer_manager_, collision_manager_);
	}
}

const int Boss2State1::start_shooting_time_ = 30;
const int Boss2State1::end_shooting_time_ = 1830-180;
const int Boss2State1::bullet_num_per_ = 2;
const int Boss2State1::shoot_period_ = 30;
const int Boss2State1::state_duration_ = 1800+60;

#include "Boss1StateNormal.h"

#include "Boss1MediatorComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "LinearMoveComponent.h"
#include "Boss1BulletCollisionComponent.h"
#include "DrawBoss1BulletComponent.h"
#include "Boss1State1.h"
#include "Boss1State2.h"
#include "Boss1State3.h"

Boss1StateNormal::Boss1StateNormal(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager, unsigned int next_state)
	:Boss1StateBase(mediator,layer_manager,score_manager,collision_manager,enemywave_manager),
	counter_(0),deg_(0.0),next_state_(next_state)
{
}

Boss1StateNormal::~Boss1StateNormal()
{
}

void Boss1StateNormal::Update()
{
	//’e‚ðŒ‚‚Âtick
	if (counter_ > 0 && counter_ % bullet_period_ == 0)
	{
		auto obj = mediator_->mObj;
		auto scene = obj->mScene;
		auto objpos = obj->GetPosition();
		double deg = deg_;
		double delta = 2 * PI / bullet_num_;
		for (int n = 0; n < bullet_num_; n++)
		{
			auto bullet = scene->AddObject(objpos, 1.0, deg);
			bullet->AddUpdateComponent<LinearMoveComponent>(MatVec::Vector2(cos(deg), sin(deg)) * bullet_speed_, 20.0);
			bullet->AddUpdateComponent<Boss1BulletCollisionComponent>(collision_manager_);
			bullet->AddOutputComponent<DrawBoss1BulletComponent>(layer_manager_);
			deg += delta;
		}
		auto& profiler = mediator_->mObj->mScene->mGame.profiler_;
		profiler.SetRecordName("add_bullet");
	}
	if (counter_ == mode_period_ - 1)
	{
		if (next_state_ == 1) {
			mediator_->ChangeState(DBG_NEW Boss1State1(mediator_, layer_manager_, score_manager_, collision_manager_,enemywave_manager_));
		}
		else if (next_state_ == 2) {
			mediator_->ChangeState(DBG_NEW Boss1State2(mediator_, layer_manager_, score_manager_, collision_manager_,enemywave_manager_));
		}
		else if (next_state_ == 3) {
			mediator_->ChangeState(DBG_NEW Boss1State3(mediator_, layer_manager_, score_manager_, collision_manager_, enemywave_manager_));
		}
	}
	deg_ += delta_deg_;
	counter_++;
}

bool Boss1StateNormal::IsInvincible()
{
	return false;
}

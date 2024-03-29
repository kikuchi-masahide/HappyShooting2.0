#include "Boss1StateEntering.h"

#include "Boss1MediatorComponent.h"
#include "../Engine/GameObject.h"
#include "Boss1StateNormal.h"

Boss1StateEntering::Boss1StateEntering(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager)
	:Boss1StateBase(mediator,layer_manager,score_manager,collision_manager,enemywave_manager)
{
	mediator_->mObj->SetPosition(MatVec::Vector2(0.0, starty_));
}

Boss1StateEntering::~Boss1StateEntering()
{
}

void Boss1StateEntering::Update()
{
	double y = (starty_ * (period_ - counter_) + endy_ * counter_) / period_;
	mediator_->mObj->SetPosition(MatVec::Vector2(0.0, y));
	counter_++;
	if (counter_ == period_)
	{
		mediator_->ChangeState(DBG_NEW Boss1StateNormal(
			mediator_,layer_manager_,score_manager_,collision_manager_,enemywave_manager_, 1
		));
	}
}

bool Boss1StateEntering::IsInvincible()
{
	return true;
}

#include "Boss2State3.h"

#include "Boss2Mediator.h"
#include "MyselfMediatorComponent.h"

Boss2State3::Boss2State3(ComponentHandle<Boss2MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager)
	:Boss2StateBase(mediator,layer_manager,score_manager,collision_manager,enemywave_manager),
	time_(0)
{
}

Boss2State3::~Boss2State3()
{
}

void Boss2State3::Update()
{
	if (time_ == 240)
	{
		mediator_->myself_mediator_->SetRetrogradePlay(2);
	}
	if (time_ == 360)
	{
		mediator_->myself_mediator_->SetProgradePlay();
		time_ = -1;
	}
	time_++;
}

bool Boss2State3::IsCollisionActive()
{
	return true;
}

bool Boss2State3::IsInvincible()
{
	return false;
}

#include "Boss2StateEntering.h"

#include "Boss2Mediator.h"
#include "../Engine/GameObject.h"
#include "Boss2State0.h"

Boss2StateEntering::Boss2StateEntering(ComponentHandle<Boss2MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager)
	:Boss2StateBase(mediator,layer_manager,score_manager,collision_manager,enemywave_manager),
	time_(0)
{
}

Boss2StateEntering::~Boss2StateEntering()
{
}

void Boss2StateEntering::Update()
{
	double y = (390.0 * min(time_, 180) + 570.0 * (180 - min(time_, 180))) / 180;
	mediator_->mObj->SetPosition(MatVec::Vector2(0, y));
	if (time_ == 239)
	{
		mediator_->ChangeState(boost::shared_ptr<Boss2State0>(new Boss2State0(
			mediator_, layer_manager_, score_manager_, collision_manager_, enemywave_manager_
		)));
	}
	time_++;
}

bool Boss2StateEntering::IsCollisionActive()
{
	return true;
}

bool Boss2StateEntering::IsInvincible()
{
	return true;
}

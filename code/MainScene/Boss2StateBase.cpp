#include "Boss2StateBase.h"

Boss2StateBase::Boss2StateBase(ComponentHandle<Boss2MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager)
	:mediator_(mediator),layer_manager_(layer_manager),score_manager_(score_manager),collision_manager_(collision_manager),enemywave_manager_(enemywave_manager)
{
}

Boss2StateBase::~Boss2StateBase()
{
}

bool Boss2StateBase::IsCollisionActive()
{
	return true;
}

bool Boss2StateBase::IsInvincible()
{
	return false;
}

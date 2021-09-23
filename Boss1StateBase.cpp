#include "stdafx.h"
#include "Boss1StateBase.h"

Boss1StateBase::Boss1StateBase(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager)
	:mediator_(mediator),layer_manager_(layer_manager),collision_manager_(collision_manager),score_manager_(score_manager)
{
}

Boss1StateBase::~Boss1StateBase()
{
}

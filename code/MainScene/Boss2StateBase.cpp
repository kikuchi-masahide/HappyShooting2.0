#include "Boss2StateBase.h"
#include "CollisionComponent.h"

Boss2StateBase::Boss2StateBase(ComponentHandle<Boss2MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager)
	:mediator_(mediator),layer_manager_(layer_manager),score_manager_(score_manager),collision_manager_(collision_manager),enemywave_manager_(enemywave_manager)
{
}

Boss2StateBase::~Boss2StateBase()
{
}

int Boss2StateBase::CheckHitComponents(std::set<ComponentHandle<CollisionComponent>>& hit_comps)
{
	int dmg = 0;
	for (auto& comp : hit_comps)
	{
		dmg += comp->GetDamage();
	}
	return dmg;
}
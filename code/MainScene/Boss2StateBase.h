#pragma once
#include "../Engine/Component.h"

class LayerManager;
class ScoreManager;
class CollisionManager;
class Boss2MediatorComponent;
class EnemyWaveManager;

class Boss2StateBase
{
public:
	Boss2StateBase(ComponentHandle<Boss2MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager);
	virtual ~Boss2StateBase();
	//親mediatorから毎tick呼び出される．
	virtual void Update() = 0;
	//コリジョンを有効ににするか否か
	virtual bool IsCollisionActive();
	//無敵であるか否か
	virtual bool IsInvincible();
protected:
	ComponentHandle<Boss2MediatorComponent> mediator_;
	boost::shared_ptr<LayerManager> layer_manager_;
	boost::shared_ptr<ScoreManager> score_manager_;
	boost::shared_ptr<CollisionManager> collision_manager_;
	boost::shared_ptr<EnemyWaveManager> enemywave_manager_;
};


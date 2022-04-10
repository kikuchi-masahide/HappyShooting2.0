#pragma once
#include "../Engine/Component.h"

class LayerManager;
class ScoreManager;
class CollisionManager;
class Boss2MediatorComponent;
class EnemyWaveManager;
class CollisionComponent;

class Boss2StateBase
{
public:
	Boss2StateBase(ComponentHandle<Boss2MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager);
	virtual ~Boss2StateBase();
	//親mediatorから毎tick呼び出される．
	virtual void Update() = 0;
	//Mediatorから呼び出される当たり判定処理
	//返り値:喰らうダメージ(返り値の分体力を減らす処理はMediator)
	//defaultは喰らったやつらの総攻撃力分シンプルに喰らうだけ
	virtual int CheckHitComponents(std::set<ComponentHandle<CollisionComponent>>& hit_comps);
protected:
	ComponentHandle<Boss2MediatorComponent> mediator_;
	boost::shared_ptr<LayerManager> layer_manager_;
	boost::shared_ptr<ScoreManager> score_manager_;
	boost::shared_ptr<CollisionManager> collision_manager_;
	boost::shared_ptr<EnemyWaveManager> enemywave_manager_;
};


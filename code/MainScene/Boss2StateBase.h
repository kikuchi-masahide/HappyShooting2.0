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
	//�emediator���疈tick�Ăяo�����D
	virtual void Update() = 0;
	//�R���W������L���ɂɂ��邩�ۂ�
	virtual bool IsCollisionActive();
	//���G�ł��邩�ۂ�
	virtual bool IsInvincible();
protected:
	ComponentHandle<Boss2MediatorComponent> mediator_;
	boost::shared_ptr<LayerManager> layer_manager_;
	boost::shared_ptr<ScoreManager> score_manager_;
	boost::shared_ptr<CollisionManager> collision_manager_;
	boost::shared_ptr<EnemyWaveManager> enemywave_manager_;
};


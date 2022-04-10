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
	//�emediator���疈tick�Ăяo�����D
	virtual void Update() = 0;
	//Mediator����Ăяo����铖���蔻�菈��
	//�Ԃ�l:��炤�_���[�W(�Ԃ�l�̕��̗͂����炷������Mediator)
	//default�͋��������̑��U���͕��V���v���ɋ�炤����
	virtual int CheckHitComponents(std::set<ComponentHandle<CollisionComponent>>& hit_comps);
protected:
	ComponentHandle<Boss2MediatorComponent> mediator_;
	boost::shared_ptr<LayerManager> layer_manager_;
	boost::shared_ptr<ScoreManager> score_manager_;
	boost::shared_ptr<CollisionManager> collision_manager_;
	boost::shared_ptr<EnemyWaveManager> enemywave_manager_;
};


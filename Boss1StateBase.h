#pragma once
#include "code/Engine/Component.h"

class LayerManager;
class ScoreManager;
class CollisionManager;
class Boss1MediatorComponent;

//TODO:���̃{�X�ɂ��K�p�\�Ȃ�Ζ��O��ς���
class Boss1StateBase
{
public:
	//���������
	//Boss1MediatorComponent��ChangeState���Ăяo���ƃC���X�^���X������C��tick����Update���Ăяo�����
	Boss1StateBase(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager);
	virtual ~Boss1StateBase();
	//�emediator���疈tick�Ăяo�����D
	virtual void Update() = 0;
	//�R���W������L���ɂɂ��邩�ۂ�
	virtual bool IsCollisionActive();
protected:
	ComponentHandle<Boss1MediatorComponent> mediator_;
	boost::shared_ptr<LayerManager> layer_manager_;
	boost::shared_ptr<ScoreManager> score_manager_;
	boost::shared_ptr<CollisionManager> collision_manager_;
};


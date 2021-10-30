#pragma once
#include "code/Engine/Component.h"

class LayerManager;
class ScoreManager;
class CollisionManager;
class Boss1MediatorComponent;

//TODO:他のボスにも適用可能ならば名前を変える
class Boss1StateBase
{
public:
	//入り口処理
	//Boss1MediatorComponentのChangeStateを呼び出すとインスタンスが作られ，次tickからUpdateが呼び出される
	Boss1StateBase(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager);
	virtual ~Boss1StateBase();
	//親mediatorから毎tick呼び出される．
	virtual void Update() = 0;
	//コリジョンを有効ににするか否か
	virtual bool IsCollisionActive();
protected:
	ComponentHandle<Boss1MediatorComponent> mediator_;
	boost::shared_ptr<LayerManager> layer_manager_;
	boost::shared_ptr<ScoreManager> score_manager_;
	boost::shared_ptr<CollisionManager> collision_manager_;
};


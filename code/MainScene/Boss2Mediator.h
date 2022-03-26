#pragma once
#include "../Engine/Component.h"

class LayerManager;
class ScoreManager;
class CollisionManager;
class EnemyWaveManager;
class DrawAnimationComponent;
class Boss2StateBase;
class MyselfMediatorComponent;

class Boss2MediatorComponent :
    public Component
{
public:
    Boss2MediatorComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager, ComponentHandle<MyselfMediatorComponent> myself_mediator);
    ~Boss2MediatorComponent();
    void Update() override;
    void ChangeState(boost::shared_ptr<Boss2StateBase> next);
    //TOCO:‘Š“–ƒ„ƒo‚¢‚±‚Æ‚µ‚Ä‚é enemywavemanager‚ÅMyselfMediator‚Á‚Ä‚é•û‚ª‚Ü‚¾ƒ}ƒV
    ComponentHandle<MyselfMediatorComponent> myself_mediator_;
private:
    boost::shared_ptr<LayerManager> layer_;
    ComponentHandle<DrawAnimationComponent> animation_;
    //‰‚ß‚Ä‚ÌUpdate‚Å0
    int time_;
    boost::shared_ptr<Boss2StateBase> state_;
};


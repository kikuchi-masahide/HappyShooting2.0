#pragma once
#include "Boss2StateBase.h"

class Boss2State0 :
    public Boss2StateBase
{
public:
    Boss2State0(ComponentHandle<Boss2MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager);
    ~Boss2State0();
    void Update() override;
    //‚Å‚Á‚©‚¢’e‚ğ‰½tick‚¨‚«‚Éo‚·‚©
    static const int bullet_period_;
    //‚Å‚Á‚©‚¢’e‚ğ‰½‰ñŒ‚‚Â‚©
    static const int bullet_repeat_;
    //‘S•”‚Å‰½tick‚±‚Ìstate‚ğ‘±‚¯‚é‚©
    static const int whole_duration_;
private:
    int time_;
};


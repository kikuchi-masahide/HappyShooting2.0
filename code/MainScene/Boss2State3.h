#pragma once
#include "Boss2StateBase.h"

class Boss2State3 :
    public Boss2StateBase
{
public:
    Boss2State3(ComponentHandle<Boss2MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager);
    ~Boss2State3();
    void Update() override;
    bool IsCollisionActive() override;
    bool IsInvincible() override;
private:
    int time_;
};


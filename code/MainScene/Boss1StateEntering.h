#pragma once
#include "Boss1StateBase.h"

class Boss1StateEntering :
    public Boss1StateBase
{
public:
    Boss1StateEntering(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager);
    ~Boss1StateEntering();
    void Update() override;
private:
    constexpr static double starty_ = 750.0;
    constexpr static double endy_ = 250.0;
    //ëçéûä‘
    constexpr static int period_ = 240;
    int counter_ = 0;
};


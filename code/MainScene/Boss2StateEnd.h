#pragma once
#include "Boss2StateBase.h"

class Boss2StateEnd :
    public Boss2StateBase
{
public:
    Boss2StateEnd(ComponentHandle<Boss2MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager);
    ~Boss2StateEnd();
    void Update() override;
    int CheckHitComponents(std::set<ComponentHandle<CollisionComponent>>& hit_comps) override;
private:
    int time_;
    boost::shared_ptr<LayerManager> layer_manager_;
};


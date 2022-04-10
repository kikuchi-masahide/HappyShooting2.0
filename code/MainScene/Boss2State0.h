#pragma once
#include "Boss2StateBase.h"

class Boss2State0 :
    public Boss2StateBase
{
public:
    Boss2State0(ComponentHandle<Boss2MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager);
    ~Boss2State0();
    void Update() override;
    //�ł������e����tick�����ɏo����
    static const int bullet_period_;
    //�ł������e�����񌂂�
    static const int bullet_repeat_;
    //�S���ŉ�tick����state�𑱂��邩
    static const int whole_duration_;
private:
    int time_;
};


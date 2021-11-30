#pragma once
#include "Boss1StateBase.h"

#include "../Engine/Math/Math.h"

class Boss1StateBeaten :
    public Boss1StateBase
{
public:
    Boss1StateBeaten(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager);
    ~Boss1StateBeaten();
    void Update() override;
    bool IsCollisionActive() override;
    bool IsInvincible() override;
private:
    //はじめてのUpdate()で0
    unsigned int counter_;
    //この場所に死亡エフェクトを発生させる
    void AddDeathEffect(MatVec::Vector2 pos, double radius = 50.0);
    std::random_device rand_dev_;
    std::default_random_engine def_rand_eng_;
    std::uniform_real_distribution<> dist_;
};


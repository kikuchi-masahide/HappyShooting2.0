#pragma once
#include "EnemyWaveBase.h"

class EnemyWave3 :
    public EnemyWaveBase
{
public:
    EnemyWave3(MainScene* main_scene);
    ~EnemyWave3();
protected:
    void OnDelete() override;
    static constexpr double bullet_speed_ = 4;
    static constexpr double bullet_size_ = 5;
    static constexpr unsigned int bullet_attack_ = 100;
    //‰½tick‚¨‚«‚É’e‚ð‘Å‚Â‚©
    static constexpr unsigned int bullet_period_ = 60;
};


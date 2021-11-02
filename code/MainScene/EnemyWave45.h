#pragma once
#include "EnemyWaveBase.h"

class EnemyWaveManager;

class EnemyWave45 :
    public EnemyWaveBase
{
public:
    EnemyWave45(MainScene* main_scene);
    ~EnemyWave45();
private:
    void OnDelete() override;
};


#pragma once
#include "EnemyWaveBase.h"

class EnemyWaveManager;

class EnemyWave45 :
    public EnemyWaveBase
{
public:
    EnemyWave45(EnemyWaveManager* manager);
    ~EnemyWave45();
private:
    void OnDelete() override;
};


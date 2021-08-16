#pragma once
#include "EnemyWaveBase.h"

class EnemyWave3 :
    public EnemyWaveBase
{
public:
    EnemyWave3(EnemyWaveManager* manager);
    ~EnemyWave3();
protected:
    void OnDelete() override;
};


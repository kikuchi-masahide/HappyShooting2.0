#pragma once
#include "EnemyWaveBase.h"

class EnemyWave1 :
    public EnemyWaveBase
{
public:
    EnemyWave1(unsigned int tick_after_clear, EnemyWaveManager* manager);
    ~EnemyWave1();
private:
    void OnDelete() override;
};


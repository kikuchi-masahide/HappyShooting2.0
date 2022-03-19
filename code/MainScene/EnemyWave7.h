#pragma once
#include "EnemyWaveBase.h"

class EnemyWave7 :
    public EnemyWaveBase
{
public:
    EnemyWave7(MainScene* main_scene);
    ~EnemyWave7();
private:
    void OnDelete() override;
};


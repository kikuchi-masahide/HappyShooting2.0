#pragma once
#include "EnemyWaveBase.h"

class EnemyWaveManager;

class EnemyWaveBoss1 :
    public EnemyWaveBase
{
public:
    EnemyWaveBoss1(MainScene* main_scene);
    ~EnemyWaveBoss1();
private:
    void OnDelete() override;
};


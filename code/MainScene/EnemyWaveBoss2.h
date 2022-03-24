#pragma once
#include "EnemyWaveBase.h"

class EnemyWaveManager;

class EnemyWaveBoss2 :
    public EnemyWaveBase
{
public:
    EnemyWaveBoss2(MainScene* main_scene);
    ~EnemyWaveBoss2();
private:
    void OnDelete() override;
};


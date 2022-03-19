#pragma once
#include "EnemyWaveBase.h"

class EnemyWave8 :
    public EnemyWaveBase
{
public:
    EnemyWave8(MainScene* main_scene);
    ~EnemyWave8();
private:
    void OnDelete() override;
};


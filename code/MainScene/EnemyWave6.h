#pragma once
#include "EnemyWaveBase.h"

class EnemyWave6 :
    public EnemyWaveBase
{
public:
    EnemyWave6(MainScene* main_scene);
    ~EnemyWave6();
private:
    void OnDelete() override;
    static constexpr double startx_ = 0;
    static constexpr double starty_ = 450 + 40;
    static constexpr double abs_dx_ = 0.2;
};


#pragma once
#include "EnemyWaveBase.h"

#include "../Engine/Math/Math.h"

class EnemyWave2 :
    public EnemyWaveBase
{
public:
    EnemyWave2(unsigned int tick_after_clear, MainScene* main_scene);
    ~EnemyWave2();
private:
    void OnDelete() override;
    //Wave2で何体出てくるか
    static constexpr unsigned int all_number_ = 9;
    //総移動距離((0,450) -> (+300,50))
    static constexpr double moving_dist_ = 500.0;
    //x変化量
    static constexpr double speedx_ = +moving_dist_ * 3 / 600;
    //y変化量
    static constexpr double speedy_ = -moving_dist_ * 4 / 600;
    //1tickあたりの回転量
    static constexpr double angle_ = -PI / 60;
    //何tickの間をおいて動き出すか
    static constexpr unsigned int period_ = 10;

};


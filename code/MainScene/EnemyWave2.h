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
    //Wave2‚Å‰½‘Ìo‚Ä‚­‚é‚©
    static constexpr unsigned int all_number_ = 9;
    //‘ˆÚ“®‹——£((0,450) -> (+300,50))
    static constexpr double moving_dist_ = 500.0;
    //x•Ï‰»—Ê
    static constexpr double speedx_ = +moving_dist_ * 3 / 600;
    //y•Ï‰»—Ê
    static constexpr double speedy_ = -moving_dist_ * 4 / 600;
    //1tick‚ ‚½‚è‚Ì‰ñ“]—Ê
    static constexpr double angle_ = -PI / 60;
    //‰½tick‚ÌŠÔ‚ğ‚¨‚¢‚Ä“®‚«o‚·‚©
    static constexpr unsigned int period_ = 10;

};


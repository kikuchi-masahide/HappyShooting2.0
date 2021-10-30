#pragma once
#include "EnemyWaveBase.h"

#include "code/Engine/Math/Math.h"

class EnemyWave1 :
    public EnemyWaveBase
{
public:
    EnemyWave1(unsigned int tick_after_clear, EnemyWaveManager* manager);
    ~EnemyWave1();
private:
    void OnDelete() override;
    //Wave1‚Å‰½‘Ìo‚Ä‚­‚é‚©
    static constexpr unsigned int all_number_ = 9;
    //‘ˆÚ“®‹——£((0,450) -> (-300,50))
    static constexpr double moving_dist_ = 500.0;
    //x•Ï‰»—Ê
    static constexpr double speedx_ = -moving_dist_ * 3 / 600;
    //y•Ï‰»—Ê
    static constexpr double speedy_ = -moving_dist_ * 4 / 600;
    //1tick‚ ‚½‚è‚Ì‰ñ“]—Ê
    static constexpr double angle_ = PI / 60;
    //‰½tick‚ÌŠÔ‚ğ‚¨‚¢‚Ä“®‚«o‚·‚©
    static constexpr unsigned int period_ = 10;
};


#pragma once
#include "EnemyWaveBase.h"
#include "Math.h"

class EnemyWave1 :
    public EnemyWaveBase
{
public:
    EnemyWave1(unsigned int tick_after_clear, EnemyWaveManager* manager);
    ~EnemyWave1();
private:
    void OnDelete() override;
    //Wave1�ŉ��̏o�Ă��邩
    static constexpr unsigned int all_number_ = 9 * 2;
    //���ړ�����((0,450) -> (-300,50))
    static constexpr double moving_dist_ = 500.0;
    //�O��all_number_/2�̂�x�ω���(�㔼��*-1)
    static constexpr double speedx_ = -moving_dist_ * 3 / 600;
    //y�ω���
    static constexpr double speedy_ = -moving_dist_ * 4 / 600;
    //1tick������̉�]��
    static constexpr double angle_ = PI / 60;
    //��tick�̊Ԃ������ē����o����
    static constexpr unsigned int period_ = 10;
};


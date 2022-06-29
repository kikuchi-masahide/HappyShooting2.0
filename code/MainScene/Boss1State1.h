#pragma once
#include "Boss1StateBase.h"

//Boss1の特殊攻撃1つ目(左下，真下，右下から大きな弾をポーンと出す)
class Boss1State1 :
    public Boss1StateBase
{
public:
    Boss1State1(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager);
    ~Boss1State1();
    void Update() override;
    bool IsCollisionActive() override;
    bool IsInvincible() override;
private:
    //Update()の実行回数カウント(1回目のUpdate実行の間counter_は0である)
    unsigned int counter_;
    //1回目の弾打ち出しはcounter_が何になったらか(真下から)
    static constexpr unsigned int launch_counter_first_ = 50*60/25-1;
    //2回目の弾打ち出しはcounter_が何になったらか(左下，右下から)
    static constexpr unsigned int launch_counter_second_ = 150*60/25-1;
    //3回目の弾打ち出しはcounter_が何になったらか(左下，真下，右下から)
    static constexpr unsigned int launch_counter_third_ = 300*60/25-1;
    //弾を撃ちだす際のx座標
    static constexpr double popup_leftx_ = -150.0;
    static constexpr double popup_centerx_ = 0.0;
    static constexpr double popup_rightx_ = 150.0;
    //counter_が何になったらNormalStateに戻るか
    static constexpr unsigned int terminal_counter_ = 450*60/25-1;
    //このx座標で上下運動する，MasterBulletを追加する
    void AddMasterBullet(double x);
};


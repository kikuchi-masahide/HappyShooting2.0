#pragma once
#include "Boss1StateBase.h"

#include "Math.h"
#include "../Engine/GameObject.h"

/// <summary>
/// 膨らんだ三角形の通常弾を撃ち続けるモード
/// </summary>
class Boss1StateNormal :
    public Boss1StateBase
{
public:
    /// <param name="next_state">このモードが終了したあと，Boss1State1,3のどちらに遷移するか</param>
    Boss1StateNormal(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager, unsigned int next_state);
    ~Boss1StateNormal();
    void Update() override;
    bool IsInvincible() override;
private:
    int counter_;
    //弾を撃つ方向
    double deg_;
    //次Boss1State1~3のどちらに遷移するか
    unsigned int next_state_;
    static constexpr double delta_deg_ = PI/(60*60);
    //何個の弾を撃つか
    static constexpr int bullet_num_ = 96;
    //何tickおきに弾を撃つか．
    static constexpr int bullet_period_ = 30;
    //このモードが何tick続くか
    static constexpr int mode_period_ = 480;
    //弾速
    static constexpr double bullet_speed_ = 4.0;
};


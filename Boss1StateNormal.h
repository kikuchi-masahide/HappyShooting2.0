#pragma once
#include "Boss1StateBase.h"

#include "Math.h"

/// <summary>
/// 膨らんだ三角形の通常弾を撃ち続けるモード
/// </summary>
class Boss1StateNormal :
    public Boss1StateBase
{
public:
    Boss1StateNormal(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager);
    ~Boss1StateNormal();
    void Update() override;
private:
    int counter_;
    //弾を撃つ方向
    double deg_;
    static constexpr double delta_deg_ = PI/120;
    //何個の弾を撃つか
    static constexpr int bullet_num_ = 96;
    //何tickおきに弾を撃つか．
    static constexpr int bullet_period_ = 30;
    //このモードが何tick続くか
    static constexpr int mode_period_ = 480;
    //弾速
    static constexpr double bullet_speed_ = 4.0;
    //弾を一周分(bullet_num_個)追加する
    void AddBullet();
};


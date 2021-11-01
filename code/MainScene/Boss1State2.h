#pragma once
#include "Boss1StateBase.h"

//フヨフヨとランダムに動く弾を出すフェーズ
class Boss1State2 :
    public Boss1StateBase
{
public:
    Boss1State2(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager);
    ~Boss1State2();
    void Update() override;
    bool IsCollisionActive() override;
private:
    //x軸方向，y軸方向に弾をいくつ並べるか
    static constexpr unsigned int bullet_num_x_ = 15+1;
    static constexpr unsigned int bullet_num_y_ = 15+1;
    //上から下にグラデーションのように弾をスポーンさせる際，何tickの時間差を置いてスポーンさせるか
    static constexpr unsigned int bulletspawn_timelag_ = 10;
    unsigned int counter_;
    //counter_の初期値を何にするか(counter_が0のタイミングで弾スポーンを始める)
    static constexpr unsigned int initial_counter_ = -60;
    //何tickの間このモードで居続けるか
    static constexpr unsigned int terminal_counter_ = 60 * 25;
    //追加した弾すべて(この状態の途中でボスが倒された場合，弾はすべて消さないといけないので)
    std::vector<GameObjectHandle> bullets;
};
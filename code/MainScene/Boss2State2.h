#pragma once
#include "Boss2StateBase.h"

#include "../Engine/Math/Math.h"

//Boss2State2における、ボスの行く位置とそのタイミング
struct Boss2State2TimeTable {
public:
    int time_;
    MatVec::Vector2 pos_;
    Boss2State2TimeTable(int t, MatVec::Vector2 p) :time_(t), pos_(p) {};
};

//ボスが壁にぶつかってきてステージがぐわ～んって揺れてぶつかったとこから弾がぶわ～って出てくるやつ
class Boss2State2 :
    public Boss2StateBase
{
public:
    Boss2State2(ComponentHandle<Boss2MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager);
    ~Boss2State2();
    void Update() override;
    bool IsCollisionActive() override;
    bool IsInvincible() override;
    //timetable_[n].time_のとき表示位置がtimetable_[n].pos_であるように移動する 間は線形補完
    static const Boss2State2TimeTable timetable_[16];
private:
    int time_;
    //四方に弾をばらまく
    void Shoot();
    //このstateを維持する時間
    static const int state_duration_;
    //カベにぶつかったとき何個弾を放出するか
    static const int bullet_num_;
};


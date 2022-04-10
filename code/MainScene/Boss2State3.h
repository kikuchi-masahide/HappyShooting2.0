#pragma once
#include "Boss2StateBase.h"

class Boss2State3Bullet;

class Boss2State3 :
    public Boss2StateBase
{
public:
    Boss2State3(ComponentHandle<Boss2MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager);
    ~Boss2State3();
    void Update() override;
private:
    int time_;
    //次何個の群を生成するか
    int wave_num_;
    //最初に弾を出すときの、正五角形の半径
    static const double r0_;
    //第一群は、何tickに一個のペースで弾を生成するか(できれば60の約数であってほしい)
    static const int bullet_gen_freq_;
    std::vector<ComponentHandle<Boss2State3Bullet>> bullets_;
    //第n周の、m群目の弾を生成する(計5個)
    void GenerateBullets(int n, int m);
    //自機・自機弾・自分が撃った球をすべて順行再生させる(ついでに死んでるハンドルを削除)
    void SetProgradePlay();
    //自機・自機弾・自分が撃った球をすべて逆行再生させる
    void SetRetrogradePlay(unsigned int speed);
};


#pragma once
#include "../Engine/Component.h"

class LayerManager;
class ScoreManager;
class EnemyWaveManager;
class CollisionManager;
class DrawAnimationComponent;
class EnemyHealthComponent;

class Enemy6MediatorComponent :
    public Component
{
public:
    /// <summary>
    /// time,x0,y0,dx,lifeは親から引き継がれる
    /// </summary>
    /// <param name="time">カウンター(0スタート)</param>
    /// <param name="x0">最初の位置</param>
    /// <param name="y0">最初の位置</param>
    /// <param name="dx">毎tickのx移動量</param>
    /// <param name="life">体力</param>
    Enemy6MediatorComponent(GameObjectHandle _handle, int time, double x0, double y0, double dx, int life,
        boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager,
        boost::shared_ptr<EnemyWaveManager> enemywave_manager,
        boost::shared_ptr<CollisionManager> collision_manager);
    ~Enemy6MediatorComponent();
    void Update() override;
    //ライフ初期値
    static constexpr int life0_ = 3000;
private:
    //複製処理
    void Clone();
    ComponentHandle<DrawAnimationComponent> animation_;
    ComponentHandle<EnemyHealthComponent> health_;
    //timeがこの値になるUpdateまで実行する
    constexpr static int lifetime_ = 60*20 - 1;
    //この時間ごとに分裂する
    constexpr static int clone_cycle_ = 60 * 4;
    //y変化量
    static constexpr double dy_ = -0.5;
    //1tickあたりの移動量
    double dx_;
    int life_;
    int time_;
    boost::shared_ptr<LayerManager> layer_manager_;
    boost::shared_ptr<ScoreManager> score_manager_;
    boost::shared_ptr<EnemyWaveManager> enemywave_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    //死に際の攻撃
    void DeathAttack();
};


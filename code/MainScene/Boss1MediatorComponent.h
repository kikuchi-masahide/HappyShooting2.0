#pragma once
#include "../Engine/Component.h"

class LayerManager;
class ScoreManager;
class EnemyWaveManager;
class CollisionManager;
class Boss1StateBase;
class DrawBoss1Component;

class Boss1MediatorComponent :
    public Component
{
public:
    Boss1MediatorComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager, boost::shared_ptr<CollisionManager> collision_manager);
    ~Boss1MediatorComponent();
    void Update() override;
    void ChangeState(Boss1StateBase* next_state);
    //アニメーションをストップする(pause == true -> ストップする)
    void PauseAnimation(bool pause);
    //四角形の回転角度を得る
    double GetSquareGrad();
    //四角形の中心とオブジェクト座標の距離を得る
    double GetSquareCenterDist();
    //コリジョンを有効にするか返す
    bool IsCollisionActive();
    /// <summary>
    /// ダメージを与える
    /// </summary>
    /// <returns>実際に喰らったダメージ(体力100で200ダメの弾を当てられると実ダメージは100，無敵中に当たっても0,...)</returns>
    double Damage(double damage);
    /// <summary>
    /// 残りの体力が，全体力に占める割合を返す
    /// </summary>
    double GetHealthRate();
private:
    boost::shared_ptr<LayerManager> layer_manager_;
    boost::shared_ptr<ScoreManager> score_manager_;
    boost::shared_ptr<EnemyWaveManager> enemywave_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    Boss1StateBase* current_state_;
    ComponentHandle<DrawBoss1Component> draw_component_;
    //アニメーションが止まっているか否か(次tickからの適用)
    bool is_pausing_;
    //初期体力
    static constexpr double all_health_ = 300.0;//30000.0;
    //現体力
    double health_;
    //ヘルスバーを描く位置調整のためのオブジェクト
    GameObjectHandle healthbar_object_;
    //ヘルスバーの位置，幅，高さ
    static constexpr double healthbar_x_ = 0.0;
    static constexpr double healthbar_y_ = 430.0;
    static constexpr double healthbar_w_ = 500.0;
    static constexpr double healthbar_h_ = 5.0;
};


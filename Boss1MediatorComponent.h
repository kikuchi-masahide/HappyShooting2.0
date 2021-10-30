#pragma once
#include "code/Engine/Component.h"

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
    //Boss1にダメージを与える
    //TODO:HealthComponentを乗せたら処理内容を書く
    void GetDamaged(unsigned int damage);
private:
    boost::shared_ptr<LayerManager> layer_manager_;
    boost::shared_ptr<ScoreManager> score_manager_;
    boost::shared_ptr<EnemyWaveManager> enemywave_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    Boss1StateBase* current_state_;
    ComponentHandle<DrawBoss1Component> draw_component_;
    //アニメーションが止まっているか否か(次tickからの適用)
    bool is_pausing_;
};


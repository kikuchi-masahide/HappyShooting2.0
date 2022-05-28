#pragma once
#include "../Engine/Component.h"

class LayerManager;
class ScoreManager;
class CollisionManager;
class EnemyWaveManager;
class DrawAnimationComponent;
class Boss2StateBase;
class MyselfMediatorComponent;
class CollisionComponent;
template<class T>
class DrawHealthBarComponent;

class Boss2MediatorComponent :
    public Component
{
public:
    Boss2MediatorComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager, ComponentHandle<MyselfMediatorComponent> myself_mediator);
    ~Boss2MediatorComponent();
    void Update() override;
    void ChangeState(boost::shared_ptr<Boss2StateBase> next);
    //TOCO:相当ヤバいことしてる enemywavemanagerでMyselfMediator持ってる方がまだマシ
    ComponentHandle<MyselfMediatorComponent> myself_mediator_;
    double GetHealthRate();
    //CollisionComponentから呼び出される 具体的な処理はStateに任せる
    void CheckHitComponent(std::set<ComponentHandle<CollisionComponent>>& hit_comps);
    //Boss2とヘルスバーの描画を不可逆的にストップする
    void HaltDrawing();
private:
    boost::shared_ptr<LayerManager> layer_;
    boost::shared_ptr<ScoreManager> score_;
    boost::shared_ptr<CollisionManager> col_;
    boost::shared_ptr<EnemyWaveManager> enemy_;
    ComponentHandle<DrawAnimationComponent> animation_;
    ComponentHandle<DrawHealthBarComponent<Boss2MediatorComponent>> health_bar_;
    //初めてのUpdateで0
    int time_;
    boost::shared_ptr<Boss2StateBase> state_;
    int health_;
    //初期体力
    static constexpr int health0_ = 300;
    static constexpr double healthbar_x_ = 0.0;
    static constexpr double healthbar_y_ = 430.0;
    static constexpr double healthbar_w_ = 500.0;
    static constexpr double healthbar_h_ = 5.0;
    //一緒に道連れにしないといけないので
    GameObjectHandle health_bar_obj_;
};


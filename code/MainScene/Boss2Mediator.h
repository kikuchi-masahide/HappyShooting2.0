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

class Boss2MediatorComponent :
    public Component
{
public:
    Boss2MediatorComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager, ComponentHandle<MyselfMediatorComponent> myself_mediator);
    ~Boss2MediatorComponent();
    void Update() override;
    void ChangeState(boost::shared_ptr<Boss2StateBase> next);
    //TOCO:�������o�����Ƃ��Ă� enemywavemanager��MyselfMediator�����Ă�����܂��}�V
    ComponentHandle<MyselfMediatorComponent> myself_mediator_;
    double GetHealthRate();
    //CollisionComponent����Ăяo����� ��̓I�ȏ�����State�ɔC����
    void CheckHitComponent(std::set<ComponentHandle<CollisionComponent>>& hit_comps);
private:
    boost::shared_ptr<LayerManager> layer_;
    boost::shared_ptr<ScoreManager> score_;
    ComponentHandle<DrawAnimationComponent> animation_;
    //���߂Ă�Update��0
    int time_;
    boost::shared_ptr<Boss2StateBase> state_;
    int health_;
    //�����̗�
    static constexpr int health0_ = 300000;
    static constexpr double healthbar_x_ = 0.0;
    static constexpr double healthbar_y_ = 430.0;
    static constexpr double healthbar_w_ = 500.0;
    static constexpr double healthbar_h_ = 5.0;
};

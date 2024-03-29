#pragma once
#include "../Engine/Component.h"

class LayerManager;
class CollisionManager;
class EnemyWaveManager;
class MyBulletComponent;

class MyselfAddAimBulletComponent :
    public Component
{
public:
    MyselfAddAimBulletComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col, boost::shared_ptr<EnemyWaveManager> enemy);
    ~MyselfAddAimBulletComponent();
    void Update() override;
    bool is_active_;
    //次tickから順行再生を行う
    void SetProgradePlay();
    //次tickからspeed倍速で逆行再生を行う
    void SetRetrogradePlay(unsigned int speed);
private:
    boost::shared_ptr<LayerManager> layer_;
    boost::shared_ptr<CollisionManager> collision_;
    boost::shared_ptr<EnemyWaveManager> enemy_;
    unsigned int time_;
    //このtick数おきに弾を追加
    static constexpr unsigned int period_to_fire_ = 15;
    //弾の1tickでの移動距離
    static constexpr double moving_dist_ = 8.0;
    //弾の半径
    static constexpr double bullet_redius_ = 5.0;
    //2対のうち片方から弾を出す(i=1,-1,toは撃つ対象)
    void ShootFrom(int i, GameObjectHandle to);
    int speed_;
    std::vector<ComponentHandle<MyBulletComponent>> bullets_;
};


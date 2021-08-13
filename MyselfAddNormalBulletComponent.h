#pragma once
#include "Component.h"
#include "GameObjectHandle.h"

class LayerManager;
class CollisionManager;

//8tickおきに自機通常弾を追加
class MyselfAddNormalBulletComponent :
    public Component
{
public:
    MyselfAddNormalBulletComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<CollisionManager> collision_manager);
    ~MyselfAddNormalBulletComponent();
    void Update() override;
private:
    //弾の1tickでの移動距離
    static constexpr double moving_dist_ = 8;
    //弾の半径
    static constexpr double bullet_redius_ = 5;
    //このtick数おきに弾を追加
    static constexpr unsigned int period_to_fire_ = 8;
    boost::shared_ptr<LayerManager> layer_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    //時間 Updateの最後で加算
    unsigned int time_;
};


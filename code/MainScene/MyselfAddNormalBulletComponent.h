#pragma once
#include "../Engine/Component.h"
#include "../Engine/GameObject.h"

class LayerManager;
class CollisionManager;
class MyBulletComponent;

//8tickおきの通常自機弾追加、およびそれらの管理(順行・逆行再生に対応させる)
class MyselfAddNormalBulletComponent :
    public Component
{
public:
    MyselfAddNormalBulletComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<CollisionManager> collision_manager);
    ~MyselfAddNormalBulletComponent();
    void Update() override;
    //弾うつならばtrueにする
    bool is_active_;
    //次tickから順行再生を行う
    void SetProgradePlay();
    //次tickからspeed倍速で逆再生を行う
    void SetRetrogradePlay(unsigned int speed);
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
    int time_;
    //自分が撃った弾のvector LinearMoveRevComponentだけ持っておけばよい
    std::vector<ComponentHandle<MyBulletComponent>> bullets_;
    //再生時間
    int speed_;
};


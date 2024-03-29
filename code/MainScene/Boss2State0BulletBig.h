#pragma once
#include "../Engine/Component.h"

class LayerManager;
class CollisionManager;

class Boss2State0BulletBig :
    public Component
{
public:
    /// <param name="inv">始めに弾の動く方向を反転して左から右にするか否か</param>
    Boss2State0BulletBig(GameObjectHandle obj, bool inv, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<CollisionManager> collision_manager);
    ~Boss2State0BulletBig();
    void Update() override;
private:
    int time_;
    boost::shared_ptr<LayerManager> layer_;
    boost::shared_ptr<CollisionManager> collision_;
    //何tick間隔で弾を生成するか
    static const int bullet_period_;
    //弾を生成するとき一気に何個作るか
    static const int bullet_num_per_;
    //でっかい弾の進む方向
    //x軸方向は必要に応じて正負反転
    static const double bullet_dx0_;
    static const double bullet_dy_;
    //でっかい弾の半径
    static const double bullet_radius_;
    double bullet_dx_;
};


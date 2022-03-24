#pragma once
#include "../Engine/Component.h"

class LayerManager;
class CollisionManager;

//Boss2State1で上下から飛んでくる弾の初期化、更新を行う
class Boss2State1Bullet :
    public Component
{
public:
    Boss2State1Bullet(GameObjectHandle obj,bool go_down, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col);
    ~Boss2State1Bullet();
    void Update() override;
private:
    //加速度の絶対値
    static const double abs_g_;
    //速度の絶対値最大
    static const double max_v_;
    double v_;
    bool go_down_;
};


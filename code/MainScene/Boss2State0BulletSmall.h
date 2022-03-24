#pragma once
#include "../Engine/Component.h"

class LayerManager;
class CollisionManager;
class DrawNormalBulletComponent;
class NormalBulletCollisionComponent;

/// <summary>
/// Boss2State0の、でっかい弾から生まれる小さいのの初期化、更新
/// ただし、位置の初期化だけはでっかい方から行う
/// </summary>
class Boss2State0BulletSmall :
    public Component
{
public:
    Boss2State0BulletSmall(GameObjectHandle obj, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col);
    ~Boss2State0BulletSmall();
    void Update() override;
private:
    //y軸方向の加速度
    static const double g_;
    //何tickの間当たり判定を活かし続けるか
    static const int whole_duration_;
    //当たり判定消失からオブジェクト消失に何tickかけるか
    static const int fadeout_period_;
    //弾の半径
    static const double radius_;
    //y軸方向の速度、加速度
    double v_;
    double a_;
    int time_;
    ComponentHandle<DrawNormalBulletComponent> draw_;
    ComponentHandle<NormalBulletCollisionComponent> col_;
};


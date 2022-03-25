#pragma once
#include "../Engine/Component.h"

class LayerManager;
class CollisionManager;
class DrawNormalBulletComponent;
class NormalBulletCollisionComponent;

//Boss2State2の弾の、初期位置以外の初期化・更新を行う
class Boss2State2Bullet :
    public Component
{
public:
    Boss2State2Bullet(GameObjectHandle obj, double deg, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col);
    ~Boss2State2Bullet();
    void Update() override;
private:
    //どの方向に飛んでいくか
    double deg_;
    //現在の速度絶対値
    double abs_v_;
    int time_;
    ComponentHandle<DrawNormalBulletComponent> draw_;
    ComponentHandle<NormalBulletCollisionComponent> col_;
    //加速度絶対値(速度は-abs_g_Δtで減少させる)
    static const double abs_g_;
    //初速絶対値
    static const double abs_v0_;
    //速度絶対値の最小
    static const double abs_v_min_;
    //弾の半径
    static const double radius_;
    //何tickの間当たり判定を持ち完全不透明で描画するか
    static const int lifetime_;
    //何tickでα:1->0で消失するか
    static const int fadeout_;
};


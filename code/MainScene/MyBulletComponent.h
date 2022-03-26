#pragma once
#include "../Engine/Component.h"

#include "../Engine/Math/Math.h"

class LayerManager;
class CollisionManager;
class MyBulletCollisionComponent;
class DrawNormalBulletComponent;

//逆行再生を行える、自機弾用のメディエータ
//当たり判定・描画の初期化およびコントロールも行う
class MyBulletComponent :
    public Component
{
public:
    MyBulletComponent(GameObjectHandle obj,boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col, MatVec::Vector2 d, double radius);
    ~MyBulletComponent();
    void Update() override;
    //次tickから順行再生を行う
    void SetProgradePlay();
    //次tickからspeed倍速で逆再生を行う(その過程で生起位置に戻ったら消滅)
    void SetRetrogradePlay(unsigned int speed);
    //MyBulletCollisionComponentから呼び出される、衝突報告用関数
    void NoticeCollision();
private:
    MatVec::Vector2 d_;
    double radius_;
    //再生速度 1以下かつ0でない整数、1ならば順行、負ならば逆行
    //Set~Playから設定
    int speed_;
    //一度画面外に出てから何tickの間生存させておくか
    //(画面外に出てからこれ以上の時間が経ったオブジェクトは逆再生できない)
    static const int grace_time_;
    //逆再生中、これが負になる直前のtickで消滅
    int time_;
    //時間time_までで、画面内に最後にいた、または敵に当たっていなかったときのtime_の値
    //逆行再生中はこの値を小さくしていく
    int last_time_in_stage_;
    //当たり判定
    ComponentHandle<MyBulletCollisionComponent> collision_;
    //描画
    ComponentHandle<DrawNormalBulletComponent> draw_;
};


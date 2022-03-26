#pragma once
#include "../Engine/Component.h"

#include "../Engine/Math/Math.h"

class LayerManager;
class CollisionManager;
class Boss2State3BulletColComponent;
class DrawNormalBulletComponent;

//逆行再生に関する記述は、MyBulletComponent参照
class Boss2State3Bullet :
    public Component
{
public:
    Boss2State3Bullet(GameObjectHandle obj, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col);
    ~Boss2State3Bullet();
    void Update() override;
    void SetProgradePlay();
    void SetRetrogradePlay(unsigned int speed);
private:
    //弾の半径
    static const double radius_;
    //弾の速度
    static const double v_;
    static const int grace_time_;
    int speed_;
    int time_;
    int last_time_in_stage_;
    ComponentHandle<Boss2State3BulletColComponent> collision_;
    ComponentHandle<DrawNormalBulletComponent> draw_;
    //始めの位置(位置復元に必要)
    MatVec::Vector2 pos0_;
    //時間tから位置を求める
    MatVec::Vector2 SolvePosWhen(int time);
    //時間tから透明度を求める
    double SolveAlphaWhen(int time);
};


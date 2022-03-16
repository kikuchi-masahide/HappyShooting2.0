#pragma once
#include "MyselfArmorBase.h"

#include "../Engine/Component.h"

class MyselfMediatorComponent;
class MyselfAddNormalBulletComponent;
class MyselfAddAimBulletComponent;
class DrawAnimationComponent;
class LayerManager;
class CollisionManager;
class EnemyWaveManager;

/// <summary>
/// 横に敵機誘導弾がくっつく
/// </summary>
class MyselfArmor2 :
    public MyselfArmorBase
{
public:
    MyselfArmor2(ComponentHandle<MyselfMediatorComponent> med, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col, boost::shared_ptr<EnemyWaveManager> enemy);
    ~MyselfArmor2();
    void Update() override;
    void UpdateAlpha(double alpha) override;
    void SetBulletAvailability(bool act) override;
private:
    ComponentHandle<DrawAnimationComponent> animation_;
    ComponentHandle<MyselfAddNormalBulletComponent> normal_bullet_;
    ComponentHandle<MyselfAddAimBulletComponent> aim_bullet_;
    boost::shared_ptr<LayerManager> layer_;
    boost::shared_ptr<CollisionManager> collision_;
    boost::shared_ptr<EnemyWaveManager> enemy_;
    //弾発射していいか
    bool is_bullet_active_;
    //インスタンス生成からの経過tick
    //180からはアニメーションを止め、敵機誘導弾の発射を開始する
    unsigned int time_;
};


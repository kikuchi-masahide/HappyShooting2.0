#pragma once
#include "MyselfArmorBase.h"

#include "../Engine/Component.h"

class MyselfMediatorComponent;
class MyselfAddNormalBulletComponent;
class LayerManager;
class CollisionManager;
class DrawTextureComponent;

//自機身一つでまっすぐ弾を撃つだけ 一番最初の武器形態
//TODO:本当だったら、当たり判定・自機描画・武器装備って、Builderクラスの出番ですか?今回多分しないけど
class MyselfArmorAlone :
    public MyselfArmorBase
{
public:
    MyselfArmorAlone(ComponentHandle<MyselfMediatorComponent> med, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col);
    ~MyselfArmorAlone() override;
    void Update() override;
    void UpdateAlpha(double alpha) override;
    void SetBulletAvailability(bool act) override;
private:
    ComponentHandle<DrawTextureComponent> texture_;
    ComponentHandle<MyselfAddNormalBulletComponent> add_bullet_;
};


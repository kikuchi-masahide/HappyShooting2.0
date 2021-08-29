#pragma once
#include "Component.h"
#include "CollisionComponent.h"

class LayerManager;
class DrawAnimationComponent;
class DrawTextureComponent;
class DrawLazerComponent;

/// <summary>
/// 時間によりかわるEnemy4の位置，描画，当たり判定の初期化と管理を行う
/// </summary>
// TODO:当たり判定とレーザーの描画追加
class Enemy4BehaviorComponent :
    public CollisionComponent
{
public:
    Enemy4BehaviorComponent(GameObjectHandle obj, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<LayerManager> layer_manager,int flag);
    ~Enemy4BehaviorComponent();
    void Update() override;
    void CheckHitComponent() override;
private:
    int counter_;
    unsigned int mode_;
    int flag_;   //右→左に動くならば1，左→右にうごくならば-1
    ComponentHandle<DrawTextureComponent> texture0_;
    ComponentHandle<DrawAnimationComponent> animation_;
    ComponentHandle<DrawTextureComponent> texture1_;
    ComponentHandle<DrawLazerComponent> lazer_draw_;
    boost::shared_ptr<LayerManager> layer_manager_;
};


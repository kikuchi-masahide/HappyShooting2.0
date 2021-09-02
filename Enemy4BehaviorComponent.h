#pragma once
#include "Component.h"
#include "CollisionComponent.h"

#include "CircleGeometry.h"
#include "PolygonGeometry.h"

class LayerManager;
class DrawAnimationComponent;
class DrawTextureComponent;
class DrawLazerComponent;
class EnemyHealthComponent;
class ScoreManager;
class LazerCollisionComponent;

/// <summary>
/// 時間によりかわるEnemy4本体・レーザーの位置，体力，描画，当たり判定の初期化と管理を行う
/// </summary>
// TODO:当たり判定とレーザーの描画追加
class Enemy4BehaviorComponent :
    public CollisionComponent
{
public:
    Enemy4BehaviorComponent(GameObjectHandle obj, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<LayerManager> layer_manager,boost::shared_ptr<ScoreManager> score_manager,int flag);
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
    boost::shared_ptr<ScoreManager> score_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    //しっぽの半円
    CircleGeometry tail_;
    //真ん中の正方形
    PolygonGeometry center_square_;
    //パカッて開く三角形
    PolygonGeometry mouce_left_;
    PolygonGeometry mouce_right_;
    /// <summary>
    /// 当たり判定図形を設定・登録する関数を分離
    /// </summary>
    /// <param name="center">オブジェクト座標</param>
    /// <param name="deg_counter">三角形の角度をどうするか
    /// 閉じた状態をdeg_counter=0,開いた状態をdeg_counter=60とする</param>
    void RegCollisionGeometry(MatVec::Vector2 center, int deg_counter);
    //自滅するときのために保持
    ComponentHandle<EnemyHealthComponent> health_;
    //「本体にあたった」のと「レーザーに当たった」のを分けたいので
    ComponentHandle<LazerCollisionComponent> lazer_collision_;
};


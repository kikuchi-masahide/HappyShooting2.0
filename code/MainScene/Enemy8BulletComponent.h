#pragma once
#include "../Engine/Component.h"

class LayerManager;
class ScoreManager;
class CollisionManager;

/// <summary>
/// Enemy8が出す弾のコンポーネント初期化、位置更新を行う
/// </summary>
class Enemy8BulletComponent :
    public Component
{
public:
    //最初に移動する角度、自機のハンドル(途中から自機狙いになるので)
    Enemy8BulletComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager,double angle, GameObjectHandle myself);
    ~Enemy8BulletComponent();
    void Update() override;
private:
    double angle_;
    //自機ハンドル
    GameObjectHandle myself_;
    //最初のUpdate呼び出しで0
    int time_;
};


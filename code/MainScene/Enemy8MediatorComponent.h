#pragma once
#include "../Engine/Component.h"

class LayerManager;
class ScoreManager;
class EnemyWaveManager;
class CollisionManager;
class ScoreManager;
class DrawAnimationComponent;
class Enemy8CollisionComponent;

/// /// <summary>
/// Enemy8の各個体の初期化、座標変更、攻撃可・不可の設定、弾の発射を行う
/// </summary>
class Enemy8MediatorComponent :
    public Component
{
public:
    Enemy8MediatorComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col, boost::shared_ptr<ScoreManager> score, GameObjectHandle myself);
    ~Enemy8MediatorComponent();
    void Update() override;
private:
    //初めてUdpateが呼び出されるとき0、mod120を取る
    int time_;
    boost::shared_ptr<LayerManager> layer_;
    GameObjectHandle myself_;
    ComponentHandle<DrawAnimationComponent> animation_;
    ComponentHandle<Enemy8CollisionComponent> col_comp_;
    //乱数を用いて、自分の位置をランダムに変更する
    void SetPosition();
};


#pragma once
#include "../Engine/Component.h"

class LayerManager;
class ScoreManager;
class EnemyWaveManager;
class CollisionManager;
class ScoreManager;
class DrawTextureComponent;
class EnemyHealthComponent;

/// <summary>
/// Enemy7(バリア付のやつ)の本体とバリアの全初期化と管理を行う、本体のオブジェクトが持つメディエータ
/// </summary>
class Enemy7MediatorComponent :
    public Component
{
public:
    Enemy7MediatorComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col, boost::shared_ptr<ScoreManager> score);
    ~Enemy7MediatorComponent();
    void Update() override;
private:
    //初めてUpdateが呼び出されるとき-240、左右移動を始めるとき0になる
    int time_;
    ComponentHandle<DrawTextureComponent> texture_;
    boost::shared_ptr<LayerManager> layer_;
    boost::shared_ptr<CollisionManager> collision_;
    //12tickごとに4方向に弾を発射
    void Shoot();
    static const int health0_ = 2500;
};


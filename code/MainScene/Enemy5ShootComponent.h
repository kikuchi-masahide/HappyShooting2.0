#pragma once
#include "../Engine/Component.h"

#include "../Engine/Math/Math.h"

class LayerManager;
class CollisionManager;

/// <summary>
/// 自機狙い弾を一定間隔で撃つコンポーネント
/// </summary>
class Enemy5ShootComponent :
    public Component
{
public:
    /// <param name="myself">自機オブジェクト</param>
    /// <param name="radius">弾の半径</param>
    /// <param name="speed">弾の速度</param>
    /// <param name="period">撃つ間隔(カウンターが非負かつperiodで割り切れるタイミングで撃つ)</param>
    /// <param name="counter0">カウンタの初期値(最初のUpdate()でのカウンタの値がこれ)</param>
    /// <param name="attack">攻撃力</param>
    /// <param name="edge_rgb">弾の縁の色(省略時赤)</param>
    /// <param name="edge_alpha">弾の縁のα(省略時1)</param>
    Enemy5ShootComponent(GameObjectHandle handle, int priority, GameObjectHandle myself, double radius, double speed, unsigned int period, int counter0, unsigned int attack, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<CollisionManager> collision_manager, MatVec::Vector3 edge_rgb = MatVec::Vector3(1.0, 0.0, 0.0), double edge_alpha = 1.0);
    ~Enemy5ShootComponent();
    void Update() override;
private:
    GameObjectHandle myself_;
    unsigned int attack_;
    unsigned int period_;
    int counter_;
    double speed_;
    double radius_;
    boost::shared_ptr<LayerManager> layer_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    MatVec::Vector3 edge_rgb_;
    double edge_alpha_;
};


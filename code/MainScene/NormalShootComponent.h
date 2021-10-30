#pragma once
#include "../Engine/Component.h"

#include "../Engine/Math/Math.h"

class LayerManager;
class CollisionManager;

/// <summary>
/// 親オブジェクト座標から，一定方向に飛んでいく敵通常弾を一定頻度で撃つコンポーネント
/// </summary>
class NormalShootComponent :
    public Component
{
public:
    /// <param name="direction">方向</param>
    /// <param name="period">何tickに1回打つか</param>
    /// <param name="attack">攻撃力</param>
    NormalShootComponent(GameObjectHandle handle, int priority, MatVec::Vector2 direction, double radius, unsigned int period, unsigned int attack, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<CollisionManager> collision_manager, MatVec::Vector3 edge_rgb = MatVec::Vector3(1.0,0.0,0.0),double edge_alpha = 1.0);
    ~NormalShootComponent();
    void Update() override;
private:
    MatVec::Vector2 direction_;
    unsigned int attack_;
    unsigned int period_;
    unsigned int counter_;
    double radius_;
    boost::shared_ptr<LayerManager> layer_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    MatVec::Vector3 edge_rgb_;
    double edge_alpha_;
};


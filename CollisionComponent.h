#pragma once
#include "Component.h"

/// <summary>
/// 個々のオブジェクトの当たり判定
/// </summary>
class CollisionComponent :
    public Component
{
public:
    CollisionComponent(int upd_priority, unsigned int tag, unsigned int damage);
    virtual ~CollisionComponent();
    /// 自身のタグ
    const unsigned int tag_;
    unsigned int GetDamage();
    /// <summary>
    /// 前フレームの更新結果衝突したcomponent全体
    /// </summary>
    std::vector<ComponentHandle<CollisionComponent>> hit_comps;
    virtual void Update() = 0;
protected:
    unsigned int damage_;
};


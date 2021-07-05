#pragma once
#include "Component.h"
#include "CollisionManager.h"

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
    std::vector<ComponentHandle<CollisionComponent>> hit_comps_;
    virtual void Update() = 0;
    /// <summary>
    /// CollisionManagerに自身の持つ幾何図形を追加する
    /// CollisionManager::AddCollisionComponentで自身を登録すると，この関数がCollisionManagerの当たり判定直前に呼び出される，
    /// </summary>
    /// <param name="manager">このコンポーネントが登録されたCollisionManager</param>
    virtual void AddGeometryToManager(CollisionManager& manager) = 0;
protected:
    unsigned int damage_;
};


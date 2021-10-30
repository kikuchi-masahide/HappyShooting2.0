#pragma once
#include "../Engine/Component.h"
#include "CollisionManager.h"

/// <summary>
/// 個々のオブジェクトの当たり判定
/// </summary>
class CollisionComponent :
    public Component
{
public:
    CollisionComponent(GameObjectHandle handle, boost::shared_ptr<CollisionManager> manager, int upd_priority, CollisionManager::Tag tag, unsigned int damage);
    virtual ~CollisionComponent();
    /// 自身のタグ
    const CollisionManager::Tag tag_;
    unsigned int GetDamage();
    /// <summary>
    /// CollisionManagerに自身の持つ幾何図形を追加する
    /// (単純なコピーとして追加するので，座標の更新はすべて終わらせておく必要がある)
    /// </summary>
    virtual void Update() = 0;
    /// <summary>
    /// CheckHitComponent実行時，このsetに衝突した全CollisionComponentが納められる
    /// </summary>
    std::set<ComponentHandle<CollisionComponent>> hit_comps_;
    /// <summary>
    /// CollisionComponentと衝突した際の処理
    /// CollisionManagerがTraverseAll()をしている最中に呼び出される
    /// </summary>
    /// <param name="hit_comps">衝突した全CollisionComponent</param>
    virtual void CheckHitComponent() = 0;
protected:
    unsigned int damage_;
    boost::shared_ptr<CollisionManager> manager_;
};


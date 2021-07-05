#pragma once
#include "ComponentHandle.h"

class CollisionComponent;

/// <summary>
/// 当たり判定コンポーネントと当たり判定図形を管理し，各コンポーネントに全フレームで衝突したコンポーネントを渡す
/// </summary>
class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();
	/// <summary>
	/// 当たり判定すべきcomponentを追加(フレーム更新)
	/// </summary>
	void AddCollisionComponent(ComponentHandle<CollisionComponent> collision_comp);
	/// <summary>
	/// 全componentが持つ図形同士の当たり判定を実行し，componentに衝突したcomponentを教える
	/// </summary>
	void TraverseAll();
private:
	//当たり判定すべきcomponent全体(各フレームでリセット)
	std::vector<ComponentHandle<CollisionComponent>> collision_comps_;
};


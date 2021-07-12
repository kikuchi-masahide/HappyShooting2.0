#pragma once

#include "Component.h"
class CollisionComponent;

/// <summary>
/// CollisionComponentで使われるべき幾何図形のインターフェース
/// </summary>
class ICollisionGeometry
{
public:
	ICollisionGeometry(ComponentHandle<CollisionComponent> parent_comp)
	:parent_comp_(parent_comp){};
	virtual ~ICollisionGeometry() {};
	//この図形を含む，辺がx,y軸に平行な長方形を返す
	virtual inline Rect2 GetAABB() const = 0;
	ComponentHandle<CollisionComponent> GetParent() const
	{
		return parent_comp_;
	}
private:
	ComponentHandle<CollisionComponent> parent_comp_;
};


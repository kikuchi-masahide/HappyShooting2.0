#pragma once

#include "Component.h"

#include "Rect2.h"

class CircleGeometry;
class CupsuleGeometry;
class PolygonGeometry;

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
	virtual inline Rect2 GetAABB() = 0;
	ComponentHandle<CollisionComponent> GetParent() const
	{
		return parent_comp_;
	}
	//この図形との当たり判定(double dispatch)
	virtual bool Dispatch(ICollisionGeometry* geometry) = 0;
	//この型の図形との当たり判定
	virtual bool IsInCollision(CircleGeometry* circle) = 0;
	virtual bool IsInCollision(CupsuleGeometry* cupsule) = 0;
	virtual bool IsInCollision(PolygonGeometry* polygon) = 0;
	//点pと線分abの距離の2乗
	static double Dist2(MatVec::Vector2 p, MatVec::Vector2 a, MatVec::Vector2 b);
	//この点が直線abの左側にあるか否か判定
	static bool IsPointOnLeft(MatVec::Vector2 p, MatVec::Vector2 a, MatVec::Vector2 b);
private:
	ComponentHandle<CollisionComponent> parent_comp_;
};


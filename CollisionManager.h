#pragma once
#include "ComponentHandle.h"

#include "CircleGeometry.h"

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
	/// 全componentが持つ図形同士の当たり判定を実行し，componentに衝突したcomponentを教える
	/// </summary>
	void TraverseAll();
	std::vector<CircleGeometry> circles_;
private:
	//この幾何図形配列をAABB左x昇順でソートしたのち，左xがこの図形のそれ以上である図形との当たり判定を行う．
	template<class T,class U>
	void TraverseAllSub(T& geometry,std::vector<U>& geometry_arr);
	//幾何図形配列全体をAABB左x昇順でソートしたのち，左xがこの図形のそれ以上である図形との当たり判定を行う．
	template<class T>
	void TraverseAllSub(T& geometry);
	//comp1とcomp2のhit_comps_に，お互いを追加する
	void NoticeEachOther(ComponentHandle<CollisionComponent> comp1, ComponentHandle<CollisionComponent> comp2);
};

template<class T,class U>
inline void CollisionManager::TraverseAllSub(T& geometry, std::vector<U>& geometry_arr)
{
	Rect2 aabb = geometry.GetAABB();

	//CircleGeometry
	int s = -1, e = geometry_arr.size();
	//geometry_arr[s].左x < aabb.左x <= geometry_arr[e].左x
	while (e - s > 1)
	{
		int m = (e + s) / 2;
		Rect2 aabb2 = geometry_arr[m].GetAABB();
		if (aabb2.GetLD()(0) < aabb.GetLD()(0))s = m;
		else e = m;
	}
	//geometry_arr[e]～の図形との当たり判定
	for (unsigned int n = e; n < geometry_arr.size(); n++)
	{
		U& geometry2 = geometry_arr[n];
		//geometryの右x<geometry2の左xになったら終了
		if (aabb.GetRU()(0) < aabb.GetLD()(0))break;
		//AABBが重ならなければ次へ(y座標を見る)
		Rect2 aabb2 = geometry2.GetAABB();
		if (
			aabb.GetRU()(1) < aabb2.GetLD()(1) ||
			aabb2.GetRU()(1) < aabb.GetLD()(1)
			)continue;
		//同じコンポーネント内の図形同士は衝突させない
		ComponentHandle<CollisionComponent> parent = geometry.GetParent();
		ComponentHandle<CollisionComponent> parent2 = geometry2.GetParent();
		if (parent == parent2)continue;
		if (geometry.IsCrossing(geometry2))
		{
			NoticeEachOther(parent,parent2);
		}
	}
}

template<class T>
inline void CollisionManager::TraverseAllSub(T& geometry)
{
	TraverseAllSub(geometry, circles_);
}

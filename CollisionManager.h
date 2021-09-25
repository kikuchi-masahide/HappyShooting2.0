#pragma once
#include "ComponentHandle.h"

#include "Math.h"
#include "CircleGeometry.h"
#include "PolygonGeometry.h"

class CollisionUIScreen;
class CollisionComponent;
class CircleGeometry;
class PolygonGeometry;
class CupsuleGeometry;

/// <summary>
/// 当たり判定コンポーネントと当たり判定図形を管理し，各コンポーネントに全フレームで衝突したコンポーネントを渡す
/// </summary>
class CollisionManager
{
public:
	CollisionManager(CollisionUIScreen* screen);
	~CollisionManager();
	/// <summary>
	/// 全componentが持つ図形同士の当たり判定を実行し，componentに衝突したcomponentを教える
	/// </summary>
	void TraverseAll();
	void AddCircleGeometry(CircleGeometry* circle);
	void AddPolygonGeometry(PolygonGeometry* polygon);
	void AddCupsuleGeometry(CupsuleGeometry* cupsule);
	//TODO:このTagに(クラス等で?)親子関係を導入し，例えば
	//My::body
	//  ::bullet
	//Enemy::body
	//     ::bullet
	//     ::lazer
	//として，「敵が持つ・敵が出した当たり判定である <==> tag == Tag::Enemy」のように書けないか?
	//(たぶんコレでそこまでやる必要はないとおもうが)
	enum class Tag :unsigned char {
		Myself,
		MyBullet,
		EnemyBody,
		EnemyBullet,
		EnemyLazer
	};
	CollisionUIScreen* const collision_ui_;
private:
	//geometryと，geometry.aabb.lx <= geometry_arr[e].aabb.lxなるgeometry_arr要素との当たり判定
	template<class T,class U>
	void TraverseAllSub_leq(T* geometry, Rect2& aabb, std::vector<std::pair<U*, Rect2>>& geometry_arr);
	//geometry_arr[ind]と，それ以降の同配列要素との当たり判定
	template<class T>
	void TraverseAllSub_same(std::vector<std::pair<T*, Rect2>>& geometry_arr, unsigned int ind);
	//geometryと，geometry.aabb.lx < geometry_arr[e].aabb.lxなるgeometry_arr要素との当たり判定
	template<class T,class U>
	void TraverseAllSub_less(T* geometry, Rect2& aabb, std::vector<std::pair<U*, Rect2>>& geometry_arr);
	//comp1とcomp2のhit_comps_に，お互いを追加する
	void NoticeEachOther(ComponentHandle<CollisionComponent> comp1, ComponentHandle<CollisionComponent> comp2);
	std::vector<std::pair<CircleGeometry*, Rect2>> circles_;
	std::vector<std::pair<PolygonGeometry*, Rect2>> polygons_;
	std::vector<std::pair<CupsuleGeometry*, Rect2>> cupsules_;
};

template<class T,class U>
inline void CollisionManager::TraverseAllSub_leq(T* geometry, Rect2& aabb, std::vector<std::pair<U*,Rect2>>& geometry_arr)
{
	//CircleGeometry
	int s = -1, e = geometry_arr.size();
	//geometry_arr[s].左x < aabb.左x <= geometry_arr[e].左x
	while (e - s > 1)
	{
		int m = (e + s) / 2;
		Rect2& aabb2 = geometry_arr[m].second;
		if (aabb2.GetLD()(0) < aabb.GetLD()(0))s = m;
		else e = m;
	}
	//geometry_arr[e]～の図形との当たり判定
	for (unsigned int n = e; n < geometry_arr.size(); n++)
	{
		U* geometry2 = geometry_arr[n].first;
		Rect2& aabb2 = geometry_arr[n].second;
		//geometryの右x<geometry2の左xになったら終了
		if (aabb.GetRU()(0) < aabb2.GetLD()(0))break;
		//AABBが重ならなければ次へ(y座標を見る)
		if (
			aabb.GetRU()(1) < aabb2.GetLD()(1) ||
			aabb2.GetRU()(1) < aabb.GetLD()(1)
			)continue;
		//同じコンポーネント内の図形同士は衝突させない
		ComponentHandle<CollisionComponent> parent = geometry->GetParent();
		ComponentHandle<CollisionComponent> parent2 = geometry2->GetParent();
		if (parent == parent2)continue;
		//TODO:...
		//自機弾同士，敵弾同士などの当たり判定を除外
		if (
			(parent->tag_ == Tag::Myself || parent->tag_ == Tag::MyBullet) &&
			(parent2->tag_ == Tag::Myself || parent2->tag_ == Tag::MyBullet)
			)continue;
		if (
			(parent->tag_ == Tag::EnemyBody || parent->tag_ == Tag::EnemyBullet || parent->tag_ == Tag::EnemyBody) &&
			(parent2->tag_ == Tag::EnemyBody || parent2->tag_ == Tag::EnemyBullet || parent->tag_ == Tag::EnemyBody)
			)continue;
		if (geometry->IsCrossing(*geometry2))
		{
			NoticeEachOther(parent,parent2);
		}
	}
}

template<class T>
inline void CollisionManager::TraverseAllSub_same(std::vector<std::pair<T*, Rect2>>& geometry_arr, unsigned int ind)
{
	T* geometry = geometry_arr[ind].first;
	Rect2& aabb = geometry_arr[ind].second;
	for (unsigned int n = ind + 1; n < geometry_arr.size(); n++)
	{
		T* geometry2 = geometry_arr[n].first;
		Rect2& aabb2 = geometry_arr[n].second;
		if (aabb.GetRU()(0) < aabb2.GetLD()(0))break;
		if (
			aabb.GetRU()(1) < aabb2.GetLD()(1) ||
			aabb2.GetRU()(1) < aabb.GetLD()(1)
			)continue;
		ComponentHandle<CollisionComponent> parent = geometry->GetParent();
		ComponentHandle<CollisionComponent> parent2 = geometry2->GetParent();
		if (parent == parent2)continue;
		//自機弾同士，敵弾同士などの当たり判定を除外
		if (
			(parent->tag_ == Tag::Myself || parent->tag_ == Tag::MyBullet) &&
			(parent2->tag_ == Tag::Myself || parent2->tag_ == Tag::MyBullet)
			)continue;
		if (
			(parent->tag_ == Tag::EnemyBody || parent->tag_ == Tag::EnemyBullet || parent->tag_ == Tag::EnemyBody) &&
			(parent2->tag_ == Tag::EnemyBody || parent2->tag_ == Tag::EnemyBullet || parent->tag_ == Tag::EnemyBody)
			)continue;
		if (geometry->IsCrossing(*geometry2))
		{
			NoticeEachOther(parent, parent2);
		}
	}
}

template<class T, class U>
inline void CollisionManager::TraverseAllSub_less(T* geometry, Rect2& aabb, std::vector<std::pair<U*, Rect2>>& geometry_arr)
{
	//CircleGeometry
	int s = -1, e = geometry_arr.size();
	//geometry_arr[s].左x <= aabb.左x < geometry_arr[e].左x
	while (e - s > 1)
	{
		int m = (e + s) / 2;
		Rect2& aabb2 = geometry_arr[m].second;
		if (aabb2.GetLD()(0) < aabb.GetLD()(0))s = m;
		else e = m;
	}
	//geometry_arr[e]～の図形との当たり判定
	for (unsigned int n = e; n < geometry_arr.size(); n++)
	{
		U* geometry2 = geometry_arr[n].first;
		Rect2& aabb2 = geometry_arr[n].second;
		//geometryの右x<geometry2の左xになったら終了
		if (aabb.GetRU()(0) < aabb2.GetLD()(0))break;
		//AABBが重ならなければ次へ(y座標を見る)
		if (
			aabb.GetRU()(1) < aabb2.GetLD()(1) ||
			aabb2.GetRU()(1) < aabb.GetLD()(1)
			)continue;
		//同じコンポーネント内の図形同士は衝突させない
		ComponentHandle<CollisionComponent> parent = geometry->GetParent();
		ComponentHandle<CollisionComponent> parent2 = geometry2->GetParent();
		if (parent == parent2)continue;
		//自機弾同士，敵弾同士などの当たり判定を除外
		if (
			(parent->tag_ == Tag::Myself || parent->tag_ == Tag::MyBullet) &&
			(parent2->tag_ == Tag::Myself || parent2->tag_ == Tag::MyBullet)
			)continue;
		if (
			(parent->tag_ == Tag::EnemyBody || parent->tag_ == Tag::EnemyBullet || parent->tag_ == Tag::EnemyBody) &&
			(parent2->tag_ == Tag::EnemyBody || parent2->tag_ == Tag::EnemyBullet || parent->tag_ == Tag::EnemyBody)
			)continue;
		if (geometry->IsCrossing(*geometry2))
		{
			NoticeEachOther(parent, parent2);
		}
	}
}

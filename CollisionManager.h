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
	//この図形の当たり判定を加える
	void AddGeometry(ICollisionGeometry* geometry);
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
	//comp1とcomp2のhit_comps_に，お互いを追加する
	void NoticeEachOther(ComponentHandle<CollisionComponent> comp1, ComponentHandle<CollisionComponent> comp2);
	std::vector<std::pair<ICollisionGeometry*, Rect2>> geometries_;
	//geometries_[n]とgeometries_[n+1]~geometries_.back()全体との当たり判定
	void TraverseAllAgainst(int target);
};
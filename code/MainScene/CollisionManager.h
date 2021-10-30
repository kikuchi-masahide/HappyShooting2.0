#pragma once
#include "../Engine/Component.h"

#include "../Engine/Math/Math.h"
#include "CircleGeometry.h"
#include "PolygonGeometry.h"
#include "AABBTree.h"

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
	//自機，自機弾等の当たり判定図形を加える
	void AddFriendlyGeometry(ICollisionGeometry* geometry);
	//敵機，敵機弾等の当たり判定図形を加える
	void AddEnemyGeometry(ICollisionGeometry* geometry);
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
	//自機，自機弾等の，敵機に攻撃する種類の当たり判定図形とそのAABBの配列
	std::vector<ICollisionGeometry*> friendly_geometries_;
	std::vector<Rect2> friendly_aabbs_;
	std::set<ComponentHandle<CollisionComponent>> friendly_comps_;
	//敵機，敵機弾等の，自機に攻撃する種類の当たり判定図形とそのAABB配列
	std::vector<ICollisionGeometry*> enemy_geometries_;
	std::vector<Rect2> enemy_aabbs_;
	std::set<ComponentHandle<CollisionComponent>> enemy_comps_;
	AABBTree aabb_tree_;
};
#pragma once
#include "EnemyBodyCollisionComponent.h"

#include "CircleGeometry.h"
#include "MainScene.h"
#include "GameObject.h"

class EnemyHealthComponent;
class ScoreManager;

/// <summary>
/// enemy1本体用の当たり判定
/// 自機，自機弾に当たったら体力減
/// </summary>
class Enemy1CollisionComponent
	:public EnemyBodyCollisionComponent
{
public:
	Enemy1CollisionComponent(GameObjectHandle object, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<ScoreManager> score_manager, ComponentHandle<EnemyHealthComponent> health);
	~Enemy1CollisionComponent();
	void Update() override;
	//衝突時のダメージ
	static constexpr double damage_ = 200;
private:
	//周りの円の方の円形当たり判定
	CircleGeometry circle_around_[3];
	//中心の円の方の円形当たり判定
	CircleGeometry circle_center_;
};


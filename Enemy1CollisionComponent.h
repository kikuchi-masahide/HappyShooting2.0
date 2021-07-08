#pragma once
#include "CollisionComponent.h"

#include "CircleGeometry.h"
#include "MainScene.h"
#include "GameObject.h"

class EnemyHealthComponent;

/// <summary>
/// enemy1本体用の当たり判定
/// 自機，自機弾に当たったら体力減
/// </summary>
class Enemy1CollisionComponent
	:public CollisionComponent
{
public:
	Enemy1CollisionComponent(MainScene* scene,GameObjectHandle object,ComponentHandle<EnemyHealthComponent> health);
	~Enemy1CollisionComponent();
	void Update() override;
	void AddGeometryToManager(CollisionManager& manager) override;
	//衝突時のダメージ
	static constexpr double damage_ = 200;
private:
	//周りの円の方の円形当たり判定
	CircleGeometry circle_around_[3];
	//中心の円の方の円形当たり判定
	CircleGeometry circle_center_;
	MainScene* scene_;
	GameObjectHandle object_;
	//ダメージ報告用
	ComponentHandle<EnemyHealthComponent> health_component_;
};


#include "stdafx.h"
#include "Enemy4BehaviorComponent.h"

#include "CollisionManager.h"
#include "GameObject.h"
#include "DrawTextureComponent.h"
#include "DrawAnimationComponent.h"
#include "DrawLazerComponent.h"
#include "EnemyHealthComponent.h"
#include "DrawHealthBarComponent.h"
#include "ScoreManager.h"
#include "LazerCollisionComponent.h"
#include "CupsuleGeometry.h"
#include "Scene.h"
#include "LinearMoveComponent.h"
#include "DrawNormalBulletComponent.h"
#include "NormalBulletCollisionComponent.h"

Enemy4BehaviorComponent::Enemy4BehaviorComponent(GameObjectHandle obj, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, int flag)
	:CollisionComponent(obj, collision_manager, 100, CollisionManager::Tag::EnemyBody, 100),
	counter_(0), mode_(0),
	flag_(flag), layer_manager_(layer_manager),score_manager_(score_manager),
	collision_manager_(collision_manager)
{
	texture0_ = mObj->AddOutputComponent<DrawTextureComponent>(layer_manager_, 9, -5.0);
	texture0_->width_ = 80.0;
	texture0_->height_ = 140.0;
	texture0_->center_offset_ = MatVec::Vector2(0.0, -30.0);
	health_ = mObj->AddUpdateComponent<EnemyHealthComponent>(layer_manager_, 9000.0);
	mObj->AddOutputComponent<DrawHealthBarComponent>(layer_manager_, health_, MatVec::Vector2(0, 25));
	tail_ = CircleGeometry(This<CollisionComponent>(), MatVec::Vector2(), 40);
	center_square_ = PolygonGeometry(This<CollisionComponent>(), 4);
	mouce_left_ = PolygonGeometry(This<CollisionComponent>(), 3);
	mouce_right_ = PolygonGeometry(This<CollisionComponent>(), 3);
}

Enemy4BehaviorComponent::~Enemy4BehaviorComponent()
{
	//アポトーシスでも，普通に倒されても，死に際に通常弾をまき散らす
	DeathAttack();
}

void Enemy4BehaviorComponent::Update()
{
	if (mode_ == 0)
	{
		//スタート位置から下に降りてくる
		MatVec::Vector2 pos((300-sqrt(2)* 20)*flag_, 500.0 - 5.0 * (double)counter_ / 4);
		mObj->SetPosition(pos);
		RegCollisionGeometry(pos, 0);
		counter_++;
		if (counter_ == 72)
		{
			//描画方法を変える
			texture0_->SetDeleteFlag();
			animation_ = mObj->AddUpdateComponent<DrawAnimationComponent>(layer_manager_, 10, 80.0, 140.0, 4, 15, -5.0, MatVec::Vector2(0.0, -30.0), 60);
			mode_ = 1;
			counter_ = 0;
		}
	}
	else if (mode_ == 1)
	{
		MatVec::Vector2 pos((300 - sqrt(2) * 20) * flag_, 410.0);
		mObj->SetPosition(MatVec::Vector2((300 - sqrt(2) * 20) * flag_, 410.0));
		//三角形2つをパカッと開く 60tick
		RegCollisionGeometry(pos, counter_);
		counter_++;
		if (counter_ == 60)
		{
			//アニメーション終了
			animation_->SetDeleteFlag();
			texture1_ = mObj->AddUpdateComponent<DrawTextureComponent>(layer_manager_, 11, -5.0);
			texture1_->width_ = 80.0;
			texture1_->height_ = 140.0;
			texture1_->center_offset_ = MatVec::Vector2(0.0, -30.0);
			//レーザー描画
			lazer_draw_ = mObj->AddOutputComponent<DrawLazerComponent>(layer_manager_, -10);
			//レーザー円の中心
			MatVec::Vector2 circle_center((300 - sqrt(2) * 20) * flag_, 370 - 40 * sqrt(2));
			lazer_draw_->a_ = circle_center;
			lazer_draw_->b_ = circle_center;
			lazer_draw_->b_(1) = -500;
			lazer_collision_ = mObj->AddUpdateComponent<LazerCollisionComponent>(collision_manager_);
			lazer_collision_->cupsule_.a_ = lazer_draw_->a_;
			lazer_collision_->cupsule_.b_ = lazer_draw_->b_;
			mode_ = 2;
			counter_ = 0;
		}
	}
	else if (mode_ == 2)
	{
		//レーザーを出す
		//円の半径を，60tickで0から20√2まで増加させる
		double r = sqrt(2) * counter_ / 3;
		lazer_draw_->r_ = r;
		lazer_collision_->cupsule_.r_ = r;
		RegCollisionGeometry(MatVec::Vector2((300 - sqrt(2) * 20) * flag_, 410.0), 60);
		counter_++;
		if (counter_ == 60)
		{
			mode_ = 3;
			counter_ = 0;
		}
	}else if(mode_ == 3)
	{
		//左(flag_ == -1ならば右)に移動
		MatVec::Vector2 pos = mObj->GetPosition();
		pos(0) -= 0.5 * flag_;
		mObj->SetPosition(pos);
		RegCollisionGeometry(pos, 60);
		//レーザーも同じように移動させる
		lazer_draw_->a_(0) = pos(0);
		lazer_draw_->b_(0) = pos(0);
		lazer_collision_->cupsule_.a_(0) = pos(0);
		lazer_collision_->cupsule_.b_(0) = pos(0);
		counter_++;
		if (counter_ == 60 * 3)
		{
			mode_ = 4;
			counter_++;
		}
	}
	else {
		RegCollisionGeometry(mObj->GetPosition(), 60);
		counter_++;
		if (counter_ == 60*12)
		{
			//自滅
			health_->Damage(9000);
			Log::OutputCritical("Enemy4 delete");
		}
	}
}

void Enemy4BehaviorComponent::CheckHitComponent()
{
	for (auto comp : hit_comps_)
	{
		auto damage = comp->GetDamage();
		auto real_damage = health_->Damage(damage);
		score_manager_->AddScore(real_damage);
	}
}

void Enemy4BehaviorComponent::RegCollisionGeometry(MatVec::Vector2 center, int deg_counter)
{
	tail_.center_ = center + MatVec::Vector2(0, 40);
	center_square_.points_[0] = center + MatVec::Vector2(-40, +40);
	center_square_.points_[1] = center + MatVec::Vector2(-40, -40);
	center_square_.points_[2] = center + MatVec::Vector2(+40, -40);
	center_square_.points_[3] = center + MatVec::Vector2(+40, +40);
	//直角三角形の斜辺じゃない方の辺の長さ
	double l = 40.0 * sqrt(2.0);
	double deg1 = 3 * PI / 4 + PI * deg_counter / 240;
	mouce_right_.points_[0] = center + MatVec::Vector2(+40, -40);
	mouce_right_.points_[1](0) = mouce_right_.points_[0](0) + l * cos(deg1);
	mouce_right_.points_[1](1) = mouce_right_.points_[0](1) + l * sin(deg1);
	deg1 += PI / 2;
	mouce_right_.points_[2](0) = mouce_right_.points_[0](0) + l * cos(deg1);
	mouce_right_.points_[2](1) = mouce_right_.points_[0](1) + l * sin(deg1);
	double deg2 = 7 * PI / 4 - PI * deg_counter / 240;
	mouce_left_.points_[0] = center + MatVec::Vector2(-40, -40);
	mouce_left_.points_[1](0) = mouce_left_.points_[0](0) + l * cos(deg2);
	mouce_left_.points_[1](1) = mouce_left_.points_[0](1) + l * sin(deg2);
	deg2 += PI / 2;
	mouce_left_.points_[2](0) = mouce_left_.points_[0](0) + l * cos(deg2);
	mouce_left_.points_[2](1) = mouce_left_.points_[0](1) + l * sin(deg2);
	manager_->AddCircleGeometry(&tail_);
	manager_->AddPolygonGeometry(&center_square_);
	manager_->AddPolygonGeometry(&mouce_left_);
	manager_->AddPolygonGeometry(&mouce_right_);
}

void Enemy4BehaviorComponent::DeathAttack()
{
	Scene* scene = mObj->mScene;
	MatVec::Vector2 objpos = mObj->GetPosition();
	for (int n = 0; n < 8; n++)
	{
		//TODO:タイミングによってAdd~Componentが死ぬのを修正する
		auto obj = scene->AddObject(objpos, 1.0, 0.0);
		if (!obj.IsValid())
		{
			return;
		}
		obj->AddUpdateComponent<LinearMoveComponent>(MatVec::DirectionVector(PI * n / 4)*4.0, 10);
		obj->AddOutputComponent<DrawNormalBulletComponent>(layer_manager_, 10.0, MatVec::Vector3(0.0, 1.0, 0.0), 1.0, -10);
		obj->AddUpdateComponent<NormalBulletCollisionComponent>(10.0, 100, collision_manager_);
	}
}
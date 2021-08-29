#include "stdafx.h"
#include "Enemy4BehaviorComponent.h"

#include "CollisionManager.h"
#include "GameObject.h"
#include "DrawTextureComponent.h"
#include "DrawAnimationComponent.h"
#include "DrawLazerComponent.h"

Enemy4BehaviorComponent::Enemy4BehaviorComponent(GameObjectHandle obj, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<LayerManager> layer_manager, int flag)
	:CollisionComponent(obj,collision_manager,100,CollisionManager::Tag::EnemyBody,100),
	counter_(0),mode_(0),
	flag_(flag),layer_manager_(layer_manager)
{
	texture0_ = mObj->AddUpdateComponent<DrawTextureComponent>(layer_manager_, 9, -5.0);
	texture0_->width_ = 80.0;
	texture0_->height_ = 140.0;
	texture0_->center_offset_ = MatVec::Vector2(0.0, -30.0);
}

Enemy4BehaviorComponent::~Enemy4BehaviorComponent()
{
}

void Enemy4BehaviorComponent::Update()
{
	if (mode_ == 0)
	{
		//スタート位置から下に降りてくる
		MatVec::Vector2 pos((300-sqrt(2)* 20)*flag_, 500.0 - 5.0 * (double)counter_ / 4);
		mObj->SetPosition(pos);
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
		pos(0) -= 1.0 * flag_;
		mObj->SetPosition(pos);
		//レーザーも同じように移動させる
		lazer_draw_->a_(0) = pos(0);
		lazer_draw_->b_(0) = pos(0);
		counter_++;
		if (counter_ == 60 * 3)
		{
			mode_ = 4;
			counter_++;
		}
	}
	else {
		counter_++;
		if (counter_ == 60*10)
		{
			Log::OutputCritical("Enemy4 delete");
			mObj->SetDeleteFlag();
		}
	}
}

void Enemy4BehaviorComponent::CheckHitComponent()
{
}

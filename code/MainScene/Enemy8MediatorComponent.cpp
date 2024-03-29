#include "Enemy8MediatorComponent.h"

#include "../Engine/GameObject.h"
#include "DrawAnimationComponent.h"
#include "EnemyHealthComponent.h"
#include "Enemy8CollisionComponent.h"
#include "DrawHealthBarComponent.h"
#include "Enemy8BulletComponent.h"

Enemy8MediatorComponent::Enemy8MediatorComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col, boost::shared_ptr<ScoreManager> score, GameObjectHandle myself)
	:Component(handle),
	time_(0),layer_(layer),myself_(myself),score_(score),collision_(col)
{
	animation_ = mObj->AddOutputComponent<DrawAnimationComponent>(layer_, 30, 60, 60, 4, 8, -5.0, MatVec::Vector2(0, 0), 31);
	auto health = mObj->AddUpdateComponent<EnemyHealthComponent>(layer_, 5000);
	col_comp_ = mObj->AddUpdateComponent<Enemy8CollisionComponent>(col, score, health);
	mObj->AddOutputComponent<DrawHealthBarComponent<EnemyHealthComponent>>(layer_, health, MatVec::Vector2(0.0, 7.5));
	SetPosition();
}

Enemy8MediatorComponent::~Enemy8MediatorComponent()
{
}

void Enemy8MediatorComponent::Update()
{
	//登場
	if (time_ < 30)
	{
		animation_->counter_ = time_;
		col_comp_->is_valid_ = false;
	}
	//とどまって弾を撃つ
	else if (time_ < 90)
	{
		animation_->counter_ = 30;
		col_comp_->is_valid_ = true;
		if (time_ == 35 || time_ == 55 || time_ == 75)
		{
			Shoot();
		}
	}
	//逃げる
	else
	{
		animation_->counter_ = 120 - time_;
		col_comp_->is_valid_ = false;
	}
	time_++;
	if (time_ == 120)
	{
		//位置を乱数で決定
		SetPosition();
		time_ = 0;
	}
}

void Enemy8MediatorComponent::SetPosition()
{
	//乱数
	static std::random_device seed_gen;
	static std::mt19937 engine(seed_gen());
	//[-1,1)乱数
	static std::uniform_real_distribution<> dist(-1.0, 1.0);
	double x, y;
	auto myself_pos = myself_->GetPosition();
	while (true)
	{
		//適当にx,yを決める
		x = dist(engine) * (300-30);
		y = dist(engine) * (450-20);
		//自機との距離が近すぎたら決めなおす
		double dist2 = (x - myself_pos(0)) * (x - myself_pos(0)) + (y - myself_pos(1)) * (y - myself_pos(1));
		if (dist2 > 100 * 100)
		{
			break;
		}
	}
	mObj->SetPosition(MatVec::Vector2(x, y));
}

void Enemy8MediatorComponent::Shoot()
{
	auto pos = mObj->GetPosition();
	for (int i = 0; i < 32; i++)
	{
		auto obj = mObj->mScene->AddObject(pos, 1.0, 0.0);
		obj->AddUpdateComponent<Enemy8BulletComponent>(layer_, score_, collision_, PI*i/16, myself_);
	}
}

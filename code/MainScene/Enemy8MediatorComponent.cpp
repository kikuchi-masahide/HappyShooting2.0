#include "Enemy8MediatorComponent.h"

#include "../Engine/GameObject.h"
#include "DrawAnimationComponent.h"
#include "EnemyHealthComponent.h"
#include "Enemy8CollisionComponent.h"
#include "DrawHealthBarComponent.h"

Enemy8MediatorComponent::Enemy8MediatorComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col, boost::shared_ptr<ScoreManager> score, GameObjectHandle myself)
	:Component(handle),
	time_(0),layer_(layer),myself_(myself)
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
	//“oê
	if (time_ < 30)
	{
		animation_->counter_ = time_;
		col_comp_->is_valid_ = false;
	}
	//‚Æ‚Ç‚Ü‚Á‚Ä’e‚ğŒ‚‚Â
	else if (time_ < 90)
	{
		animation_->counter_ = 30;
		col_comp_->is_valid_ = true;
	}
	//“¦‚°‚é
	else
	{
		animation_->counter_ = 120 - time_;
		col_comp_->is_valid_ = false;
	}
	time_++;
	if (time_ == 120)
	{
		//ˆÊ’u‚ğ—”‚ÅŒˆ’è
		SetPosition();
		time_ = 0;
	}
}

void Enemy8MediatorComponent::SetPosition()
{
	//—”
	static std::random_device seed_gen;
	static std::mt19937 engine(seed_gen());
	//[-1,1)—”
	static std::uniform_real_distribution<> dist(-1.0, 1.0);
	double x, y;
	auto myself_pos = myself_->GetPosition();
	while (true)
	{
		//“K“–‚Éx,y‚ğŒˆ‚ß‚é
		x = dist(engine) * (300-30);
		y = dist(engine) * (450-20);
		//©‹@‚Æ‚Ì‹——£‚ª‹ß‚·‚¬‚½‚çŒˆ‚ß‚È‚¨‚·
		double dist2 = (x - myself_pos(0)) * (x - myself_pos(0)) + (y - myself_pos(1)) * (y - myself_pos(1));
		if (dist2 > 100 * 100)
		{
			break;
		}
	}
	mObj->SetPosition(MatVec::Vector2(x, y));
}

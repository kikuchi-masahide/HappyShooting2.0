#include "Boss1MediatorComponent.h"

#include "Boss1StateBase.h"
#include "DrawBoss1Component.h"
#include "../Engine/GameObject.h"
#include "Boss1CollisionComponent.h"
#include "DrawHealthBarComponent.h"
#include "../Engine/Scene.h"

Boss1MediatorComponent::Boss1MediatorComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager, boost::shared_ptr<CollisionManager> collision_manager)
	:Component(object,100),
	layer_manager_(layer_manager),score_manager_(score_manager),
	enemywave_manager_(enemywave_manager),collision_manager_(collision_manager),
	current_state_(nullptr),is_pausing_(false),health_(all_health_)
{
	draw_component_ = mObj->AddOutputComponent<DrawBoss1Component>(layer_manager_, -5.0);
	mObj->AddUpdateComponent<Boss1CollisionComponent>(collision_manager_, score_manager_, This<Boss1MediatorComponent>());
	healthbar_object_ = mObj->mScene->AddObject(MatVec::Vector2(healthbar_x_, healthbar_y_), 1.0, 0.0);
	healthbar_object_->AddOutputComponent<DrawHealthBarComponent<Boss1MediatorComponent>>(layer_manager_, This<Boss1MediatorComponent>(), MatVec::Vector2(), healthbar_w_, healthbar_h_);
}

Boss1MediatorComponent::~Boss1MediatorComponent()
{
	if(current_state_)delete current_state_;
}

void Boss1MediatorComponent::Update()
{
	if (!is_pausing_)
	{
		draw_component_->t_++;
	}
	if (current_state_)
	{
		current_state_->Update();
	}
}

void Boss1MediatorComponent::ChangeState(Boss1StateBase* next_state)
{
	if (current_state_) {
		delete current_state_;
	}
	current_state_ = next_state;
}

void Boss1MediatorComponent::PauseAnimation(bool pause)
{
	is_pausing_ = pause;
}

double Boss1MediatorComponent::GetSquareGrad()
{
	return draw_component_->GetDegree();
}

double Boss1MediatorComponent::GetSquareCenterDist()
{
	return draw_component_->GetSquareCenterDist();
}

bool Boss1MediatorComponent::IsCollisionActive()
{
	if (current_state_)
	{
		return current_state_->IsCollisionActive();
	}
	return false;
}

double Boss1MediatorComponent::Damage(double damage)
{
	if (current_state_->IsInvincible())
	{
		return 0.0;
	}
	double real_damage = min(damage, health_);
	health_ -= real_damage;
	//‘Ì—Í0‚É‚È‚Á‚½‚ç€–S‰‰o‚ÉˆÚs‚·‚é
	if (health_ <= 0)
	{
		PauseAnimation(true);
	}
	return real_damage;
}

double Boss1MediatorComponent::GetHealthRate()
{
	return health_ / all_health_;
}

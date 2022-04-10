#include "Boss2Mediator.h"

#include "../Engine/GameObject.h"
#include"DrawAnimationComponent.h"
#include "Boss2StateEntering.h"
#include "DrawHealthBarComponent.h"
#include "ScoreManager.h"
#include "Boss2CollisionComponent.h"

Boss2MediatorComponent::Boss2MediatorComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager, ComponentHandle<MyselfMediatorComponent> myself_mediator)
	:Component(object,100),
	layer_(layer_manager),state_(nullptr),myself_mediator_(myself_mediator),health_(health0_),score_(score_manager)
{
	animation_ = mObj->AddOutputComponent<DrawAnimationComponent>(layer_, 31, 140, 110, 4, 8, -5.0, MatVec::Vector2(), 30);
	auto healthbar = mObj->mScene->AddObject(MatVec::Vector2(healthbar_x_, healthbar_y_), 1.0, 0.0);
	healthbar->AddOutputComponent<DrawHealthBarComponent<Boss2MediatorComponent>>(layer_, This<Boss2MediatorComponent>(), MatVec::Vector2(0, 0), healthbar_w_, healthbar_h_);
	mObj->AddUpdateComponent<Boss2CollisionComponent>(collision_manager, This<Boss2MediatorComponent>());
	ChangeState(boost::shared_ptr<Boss2StateEntering>(new Boss2StateEntering(
		This<Boss2MediatorComponent>(), layer_, score_manager, collision_manager, enemywave_manager
	)));
}

Boss2MediatorComponent::~Boss2MediatorComponent()
{
}

void Boss2MediatorComponent::Update()
{
	//30fpsで動かしてみる
	animation_->counter_ = (time_ / 2) % 30;
	if (state_)
	{
		state_->Update();
	}
	time_++;
}

void Boss2MediatorComponent::ChangeState(boost::shared_ptr<Boss2StateBase> next)
{
	state_ = next;
}

double Boss2MediatorComponent::GetHealthRate()
{
	return (double)health_ / health0_;
}

void Boss2MediatorComponent::CheckHitComponent(std::set<ComponentHandle<CollisionComponent>>& hit_comps)
{
	int dmg = state_->CheckHitComponents(hit_comps);
	dmg = min(dmg, health_);
	health_ -= dmg;
	score_->AddScore(dmg);
}

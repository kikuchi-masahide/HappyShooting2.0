#include "Boss2Mediator.h"

#include "../Engine/GameObject.h"
#include"DrawAnimationComponent.h"
#include "Boss2StateEntering.h"

Boss2MediatorComponent::Boss2MediatorComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager)
	:Component(object,100),
	layer_(layer_manager),state_(nullptr)
{
	animation_ = mObj->AddOutputComponent<DrawAnimationComponent>(layer_, 31, 140, 110, 4, 8, -5.0, MatVec::Vector2(), 30);
	ChangeState(boost::shared_ptr<Boss2StateEntering>(new Boss2StateEntering(
		This<Boss2MediatorComponent>(), layer_, score_manager, collision_manager, enemywave_manager
	)));
}

Boss2MediatorComponent::~Boss2MediatorComponent()
{
}

void Boss2MediatorComponent::Update()
{
	//30fps‚Å“®‚©‚µ‚Ä‚Ý‚é
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

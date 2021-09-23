#include "stdafx.h"
#include "Boss1StateEntering.h"

#include "Boss1MediatorComponent.h"
#include "GameObject.h"

Boss1StateEntering::Boss1StateEntering(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager)
	:Boss1StateBase(mediator,layer_manager,score_manager,collision_manager)
{
	mediator_->mObj->SetPosition(MatVec::Vector2(0.0, starty_));
}

Boss1StateEntering::~Boss1StateEntering()
{
}

void Boss1StateEntering::Update()
{
	double y = (starty_ * (period_ - counter_) + endy_ * counter_) / period_;
	mediator_->mObj->SetPosition(MatVec::Vector2(0.0, y));
	counter_++;
	if (counter_ == period_)
	{
		mediator_->ChangeState(nullptr);
	}
}

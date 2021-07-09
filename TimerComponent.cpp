#include "stdafx.h"
#include "TimerComponent.h"

TimerComponent::TimerComponent(MainScene* scene, GameObjectHandle object, unsigned int time_limit, std::function<void(MainScene*)> lambda)
	:Component(0),scene_(scene),object_(object),lambda_(lambda),time_limit_(time_limit),time_(0)
{
}

TimerComponent::~TimerComponent()
{
}

void TimerComponent::Update()
{
	if (time_ == time_limit_)
	{
		lambda_(scene_);
		object_->SetDeleteFlag();
	}
	time_++;
}

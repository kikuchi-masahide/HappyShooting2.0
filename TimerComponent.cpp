#include "stdafx.h"
#include "TimerComponent.h"

TimerComponent::TimerComponent(GameObjectHandle object, MainScene* scene, unsigned int time_limit, std::function<void(MainScene*)> lambda)
	:Component(object, 0),scene_(scene),lambda_(lambda),time_limit_(time_limit),time_(0)
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
		mObj->SetDeleteFlag();
	}
	time_++;
}

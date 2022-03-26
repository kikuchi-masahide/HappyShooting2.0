#include "LinearMoveRevComponent.h"

#include "../Engine/GameObject.h"

LinearMoveRevComponent::LinearMoveRevComponent(GameObjectHandle obj, MatVec::Vector2 d, double exist_limit)
	:Component(obj),
	d_(d),exist_limit_(exist_limit),last_time_in_stage_(-1), speed_(1)
{
}

LinearMoveRevComponent::~LinearMoveRevComponent()
{
}

void LinearMoveRevComponent::Update()
{
	auto pos = mObj->GetPosition();
	pos += d_ * speed_;
	mObj->SetPosition(pos);
	if (abs(pos(0)) < 300.0 + exist_limit_ && abs(pos(1)) < 450.0 + exist_limit_)
	{
		last_time_in_stage_ = max(last_time_in_stage_, time_);
	}
	//画面内にいた最後のときから時間が経っていたら殺す
	if (last_time_in_stage_ + grace_time_ < time_)
	{
		mObj->SetDeleteFlag();
	}
	time_ += speed_;
	//次のUpdateで生まれる前に戻りそうならば殺す
	if (time_ + speed_ < 0)
	{
		mObj->SetDeleteFlag();
	}
}

void LinearMoveRevComponent::SetProgradePlay()
{
	speed_ = 1;
}

void LinearMoveRevComponent::SetRetrogradePlay(unsigned int speed)
{
	if (speed != 0)
	{
		speed_ = -(int)(speed);
	}
}

const int LinearMoveRevComponent::grace_time_ = 480;

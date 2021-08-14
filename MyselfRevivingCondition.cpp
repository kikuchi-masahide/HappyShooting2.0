#include "stdafx.h"
#include "MyselfRevivingCondition.h"

#include "MyselfMediatorComponent.h"
#include "MyselfNormalCondition.h"
#include "DrawDeathEffectComponent.h"
#include "Scene.h"

MyselfRevivingCondition::MyselfRevivingCondition(GameObjectHandle handle, ComponentHandle<MyselfMediatorComponent> mediator)
	:MyselfConditionBase(handle,mediator),counter_(0)
{
	//死亡演出を，現座標で加えておく
	auto obj = mObj->mScene->AddObject(mObj->GetPosition(), 1.0, 0.0);
	obj->AddOutputComponent<DrawDeathEffectComponent>(mediator_->layer_manager_,-9,75);
}

MyselfRevivingCondition::~MyselfRevivingCondition()
{
}

void MyselfRevivingCondition::Update()
{
	MatVec::Vector2 pos(0, last_y_);
	pos(1) -= delta_y_ * (whole_time_ - counter_ - 1);
	mObj->SetPosition(pos);
	mediator_->SetAlpha(cos(delta_alpha_theta_ * counter_));
	counter_++;
	if (counter_ == whole_time_)
	{
		auto next = mObj->AddUpdateComponent<MyselfNormalCondition>(mediator_);
		auto next_conv = static_cast<ComponentHandle<MyselfConditionBase>>(next);
		mediator_->SetNextCondition(next_conv);
	}
}

unsigned int MyselfRevivingCondition::GetDamaged(unsigned int attack)
{
	return 0;
}

bool MyselfRevivingCondition::IsInvincible()
{
	return true;
}

#include "MyselfRevivingCondition.h"

#include "MyselfMediatorComponent.h"
#include "MyselfNormalCondition.h"
#include "DrawDeathEffectComponent.h"
#include "../Engine/Scene.h"

MyselfRevivingCondition::MyselfRevivingCondition(GameObjectHandle handle, ComponentHandle<MyselfMediatorComponent> mediator)
	:MyselfConditionBase(handle,mediator),counter_(0)
{
	scene_ = mObj->mScene;
	//死亡演出を，現座標で加えておく
	auto obj = mObj->mScene->AddObject(mObj->GetPosition(), 1.0, 0.0);
	obj->AddOutputComponent<DrawDeathEffectComponent>(mediator_->layer_manager_);
}

MyselfRevivingCondition::~MyselfRevivingCondition()
{
}

void MyselfRevivingCondition::Update()
{
	//移動後の座標を求める
	auto after_pos = mObj->GetPosition();
	if (scene_->GetKeyState('A') == ButtonState::Pressed ||
		scene_->GetKeyState('A') == ButtonState::Held)
	{
		after_pos(0) -= moving_dist_;
	}
	if (scene_->GetKeyState('D') == ButtonState::Pressed ||
		scene_->GetKeyState('D') == ButtonState::Held)
	{
		after_pos(0) += moving_dist_;
	}
	if (scene_->GetKeyState('W') == ButtonState::Pressed ||
		scene_->GetKeyState('W') == ButtonState::Held)
	{
		after_pos(1) += moving_dist_;
	}
	if (scene_->GetKeyState('S') == ButtonState::Pressed ||
		scene_->GetKeyState('S') == ButtonState::Held)
	{
		after_pos(1) -= moving_dist_;
	}
	mObj->SetPosition(after_pos);
	auto theta = delta_alpha_theta_ * counter_;
	mediator_->SetAlpha((1 + cos(theta))/2);
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

#include "stdafx.h"
#include "MyselfNormalCondition.h"

#include "code/Engine/GameObject.h"
#include "code/Engine/Scene.h"
#include "MyselfMediatorComponent.h"
#include "MyselfRevivingCondition.h"

MyselfNormalCondition::MyselfNormalCondition(GameObjectHandle handle, ComponentHandle<MyselfMediatorComponent> mediator)
	:MyselfConditionBase(handle,mediator)
{
	scene_ = mObj->mScene;
}

MyselfNormalCondition::~MyselfNormalCondition()
{
}

void MyselfNormalCondition::Update()
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
	//画面内にとどまらせる
	after_pos(0) = Max(after_pos(0), -300.0);
	after_pos(0) = Min(after_pos(0), 300.0);
	after_pos(1) = Max(after_pos(1), -450.0);
	after_pos(1) = Min(after_pos(1), 450.0);
	mObj->SetPosition(after_pos);
	mediator_->SetAlpha(1.0);
}

unsigned int MyselfNormalCondition::GetDamaged(unsigned int attack)
{
	//死んで復活状態にmediator_->condition_を譲る
	auto next = mObj->AddUpdateComponent<MyselfRevivingCondition>(mediator_);
	auto next_conv = static_cast<ComponentHandle<MyselfConditionBase>>(next);
	mediator_->SetNextCondition(next_conv);
	return attack;
}

bool MyselfNormalCondition::IsInvincible()
{
	return false;
}

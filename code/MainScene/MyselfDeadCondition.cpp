#include "MyselfDeadCondition.h"

#include "MyselfMediatorComponent.h"
#include "../Engine/Scene.h"
#include "DrawDeathEffectComponent.h"
#include "GameOverUI.h"

MyselfDeadCondition::MyselfDeadCondition(GameObjectHandle handle, ComponentHandle<MyselfMediatorComponent> mediator)
	:MyselfConditionBase(handle, mediator)
{
	mediator->SetAlpha(0.0);
	//Ž€‚ñ‚¾‰‰o‚¾‚¯‰Á‚¦‚Ä‚¨‚­
	auto obj = mObj->mScene->AddObject(mObj->GetPosition(), 1.0, 0.0);
	obj->AddOutputComponent<DrawDeathEffectComponent>(mediator_->layer_manager_);
	//GameOver...‚Ì•\Ž¦
	mObj->mScene->AddUIScreen<GameOverUI>();
}

MyselfDeadCondition::~MyselfDeadCondition()
{
}

void MyselfDeadCondition::Update()
{
}

unsigned int MyselfDeadCondition::GetDamaged(unsigned int attack)
{
	return 0;
}

bool MyselfDeadCondition::IsInvincible()
{
	return true;
}

bool MyselfDeadCondition::IsShooterActive()
{
	return false;
}


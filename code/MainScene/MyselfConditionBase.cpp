#include "MyselfConditionBase.h"

MyselfConditionBase::MyselfConditionBase(GameObjectHandle handle, ComponentHandle<MyselfMediatorComponent> mediator)
	:Component(handle,100), mediator_(mediator)
{
}

MyselfConditionBase::~MyselfConditionBase()
{
}

bool MyselfConditionBase::IsShooterActive()
{
	return true;
}

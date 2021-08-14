#include "stdafx.h"
#include "MyselfConditionBase.h"

MyselfConditionBase::MyselfConditionBase(GameObjectHandle handle, ComponentHandle<MyselfMediatorComponent> mediator)
	:Component(handle,100), mediator_(mediator)
{
}

MyselfConditionBase::~MyselfConditionBase()
{
}

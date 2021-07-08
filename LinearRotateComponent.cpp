#include "stdafx.h"
#include "LinearRotateComponent.h"

#include "GameObject.h"

LinearRotateComponent::LinearRotateComponent(GameObjectHandle object, double theta)
	:Component(100),object_(object),theta_(theta)
{
}

LinearRotateComponent::~LinearRotateComponent()
{
}

void LinearRotateComponent::Update()
{
	double angle = object_->GetRotation();
	angle += theta_;
	object_->SetRotation(angle);
}

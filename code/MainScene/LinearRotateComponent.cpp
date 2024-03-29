#include "LinearRotateComponent.h"

#include "../Engine/GameObject.h"

LinearRotateComponent::LinearRotateComponent(GameObjectHandle object, double theta)
	:Component(object, 100),theta_(theta)
{
}

LinearRotateComponent::~LinearRotateComponent()
{
}

void LinearRotateComponent::Update()
{
	double angle = mObj->GetRotation();
	angle += theta_;
	mObj->SetRotation(angle);
}

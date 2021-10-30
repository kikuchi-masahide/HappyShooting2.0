#include "Enemy5MoveComponent.h"

#include "Math.h"
#include "../Engine/GameObject.h"

Enemy5MoveComponent::Enemy5MoveComponent(GameObjectHandle obj, int counter0)
	:Component(obj),
	counter_(counter0)
{
}

Enemy5MoveComponent::~Enemy5MoveComponent()
{
}

void Enemy5MoveComponent::Update()
{
	MatVec::Vector2 pos;
	pos(0) = -150.0 * sin(PI*2*counter_ / 480);
	pos(1) = -900.0*counter_ / 480.0+450.0;
	mObj->SetPosition(pos);
	//‰æ–ÊŠO
	if (pos(1) < -450 - 20)
	{
		mObj->SetDeleteFlag();
	}
	counter_++;
}

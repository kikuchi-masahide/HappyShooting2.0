#include "stdafx.h"
#include "Enemy3MoveComponent.h"

#include "Math.h"
#include "GameObject.h"

Enemy3MoveComponent::Enemy3MoveComponent(GameObjectHandle obj, int counter0, std::function<MatVec::Vector2(double)> lambda, double angle_delta)
	:Component(obj),
	counter_(counter0),lambda_(lambda),angle_delta_(angle_delta)
{
}

Enemy3MoveComponent::~Enemy3MoveComponent()
{
}

void Enemy3MoveComponent::Update()
{
	double angle = angle_delta_*counter_;
	MatVec::Vector2 pos = lambda_(angle);
	mObj->SetPosition(pos);
	mObj->SetRotation(angle);
	counter_++;
}

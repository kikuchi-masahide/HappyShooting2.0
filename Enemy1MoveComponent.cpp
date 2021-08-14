#include "stdafx.h"
#include "Enemy1MoveComponent.h"

#include "GameObject.h"

Enemy1MoveComponent::Enemy1MoveComponent(GameObjectHandle handle, unsigned int wait_count, MatVec::Vector2 direct, double angle)
	:Component(handle,100),
	wait_count_(wait_count),counter_(0),direct_(direct),angle_(angle)
{
}

void Enemy1MoveComponent::Update()
{
	//“®‚¢‚Ä‚¢‚é‚Æ‚«
	if (counter_ >= wait_count_)
	{
		auto pos = mObj->GetPosition();
		pos += direct_;
		mObj->SetPosition(pos);
		auto angle = mObj->GetRotation();
		angle += angle_;
		mObj->SetRotation(angle);
		//ŠO‚Éo‚·‚¬‚½‚çŽ€‚Ê
		if (abs(pos(0)) > 300+abs(direct_(0)) * 10)
		{
			mObj->SetDeleteFlag();
		}
	}
	counter_++;
}

Enemy1MoveComponent::~Enemy1MoveComponent()
{
}


#include "stdafx.h"
#include "LinearMoveComponent.h"
#include "GameObject.h"

LinearMoveComponent::LinearMoveComponent(GameObjectHandle object, MatVec::Vector2 d, double exist_limit)
	:Component(object, 100),
	d_(d),exist_limit_(exist_limit)
{
}

LinearMoveComponent::~LinearMoveComponent()
{
}

void LinearMoveComponent::Update()
{
	//�I�u�W�F�N�g�ʒu�ύX
	auto pos = mObj->GetPosition();
	pos += d_;
	mObj->SetPosition(pos);
	//�ʒu�̃`�F�b�N
	if (abs(pos(0)) > 300 + exist_limit_ || abs(pos(1)) > 450 + exist_limit_)
	{
		mObj->SetDeleteFlag();
	}
}

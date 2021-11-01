#include "AcceleratedMoveComponent.h"

#include "../Engine/GameObject.h"

AcceleratedMoveComponent::AcceleratedMoveComponent(GameObjectHandle obj, int prio, MatVec::Vector2 initial_pos, MatVec::Vector2 initial_v, MatVec::Vector2 a)
	:Component(obj,prio),
	v_(initial_v),a_(a)
{
	mObj->SetPosition(initial_pos);
}

void AcceleratedMoveComponent::Update()
{
	auto pos = mObj->GetPosition();
	pos += v_;
	mObj->SetPosition(pos);
	v_ += a_;
	//��ʂ�1.5�{�O�ɏo������߂ď��ł�����
	if (abs(pos(0)) > 300.0*3/2 || abs(pos(1)) > 450.0*3/2)
	{
		mObj->SetDeleteFlag();
	}
}

AcceleratedMoveComponent::~AcceleratedMoveComponent()
{
}

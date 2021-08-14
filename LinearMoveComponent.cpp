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
	//オブジェクト位置変更
	auto pos = mObj->GetPosition();
	pos += d_;
	mObj->SetPosition(pos);
	//位置のチェック...これから先画面外に現れることがないならば死ぬ
	int txbo = -1e7;
	int txto = 1e7;
	int tybo = -1e7;
	int tyto = 1e7;
	if (!Zero(d_(0)))
	{
		if (d_(0) > 0) {
			txbo = ceil((-exist_limit_ - 300 - pos(0)) / d_(0));
			txto = floor((exist_limit_ + 300 - pos(0)) / d_(0));
		}
		else {
			txbo = ceil((exist_limit_ + 300 - pos(0)) / d_(0));
			txto = floor((-exist_limit_ - 300 - pos(0)) / d_(0));
		}
	}
	if (!Zero(d_(1)))
	{
		if (d_(1) > 0) {
			txbo = ceil((-exist_limit_ - 450 - pos(1)) / d_(1));
			txto = floor((exist_limit_ + 450 - pos(1)) / d_(1));
		}
		else {
			txbo = ceil((exist_limit_ + 450 - pos(1)) / d_(1));
			txto = floor((-exist_limit_ - 450 - pos(1)) / d_(1));
		}
	}
	if (max(txbo, tybo) > min(txto, tyto) || min(txto, tyto) < 0)
	{
		mObj->SetDeleteFlag();
	}
}

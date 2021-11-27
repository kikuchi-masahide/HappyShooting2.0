#include "MyselfPosAdjustComponent.h"

#include "../Engine/GameObject.h"

MyselfPosAdjustComponent::MyselfPosAdjustComponent(GameObjectHandle handle, GameObjectHandle myself, MatVec::Vector2 a, MatVec::Vector2 b)
	:Component(handle,100),
	myself_(myself)
{
	SetAnchorPoint(a, b);
}

MyselfPosAdjustComponent::~MyselfPosAdjustComponent()
{
}

void MyselfPosAdjustComponent::Update()
{
	//現在位置
	MatVec::Vector2 curpos = myself_->GetPosition();
	auto d = b_ - a_;
	//直線の右側を向いている垂線
	MatVec::Vector2 n(d(1), -d(0));
	//自機位置から直線へおろした垂線の足をy=a+tdとおく(t is a real number)
	double t = MatVec::Dot(curpos - a_, d)/d.Norm2();
	auto y = a_ + t * d;
	//y-curposがnの正数倍の時，自機は禁止領域にいるので移動させる
	auto dif = y - curpos;
	if (!Zero(n(0)))
	{
		if (dif(0) / n(0) > 0)
		{
			myself_->SetPosition(y);
		}
	}
	else if (!Zero(n(1)))
	{
		if (dif(1) / n(1) > 0)
		{
			myself_->SetPosition(y);
		}
	}
}

void MyselfPosAdjustComponent::SetAnchorPoint(MatVec::Vector2 a, MatVec::Vector2 b)
{
	//2点が直線を構成していない
	BOOST_ASSERT(!Zero((b - a).Norm2()));
	a_ = a;
	b_ = b;
}


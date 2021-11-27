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
	//���݈ʒu
	MatVec::Vector2 curpos = myself_->GetPosition();
	auto d = b_ - a_;
	//�����̉E���������Ă��鐂��
	MatVec::Vector2 n(d(1), -d(0));
	//���@�ʒu���璼���ւ��낵�������̑���y=a+td�Ƃ���(t is a real number)
	double t = MatVec::Dot(curpos - a_, d)/d.Norm2();
	auto y = a_ + t * d;
	//y-curpos��n�̐����{�̎��C���@�͋֎~�̈�ɂ���̂ňړ�������
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
	//2�_���������\�����Ă��Ȃ�
	BOOST_ASSERT(!Zero((b - a).Norm2()));
	a_ = a;
	b_ = b;
}


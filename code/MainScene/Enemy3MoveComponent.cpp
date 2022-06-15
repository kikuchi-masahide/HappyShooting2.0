#include "Enemy3MoveComponent.h"

#include "Math.h"
#include "../Engine/GameObject.h"

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
	//HACK:��ʒ��S�ɓG�@����������ۂɂ���
	//DrawTextureComponent�̖{�ǉ����̂͐������x�点���Ă��邪�AMainSceneBaseLayer�ւ̖��߂̓R���X�g���N�^
	//�Ŏ��O�ɔ�΂���Ă���̂������B��͂�x�����������s��Ȃ��Ɖ������Ȃ���
	double angle = angle_delta_*counter_;
	MatVec::Vector2 pos = lambda_(angle);
	mObj->SetPosition(pos);
	mObj->SetRotation(angle);
	//��ʊO
	double x = pos(0);
	if (abs(x) > 300.0 + 20.0) {
		mObj->SetDeleteFlag();
	}
	counter_++;
}

#include "MyselfRetrogradeCondition.h"

#include "MyselfMediatorComponent.h"

MyselfRetrogradeCondition::MyselfRetrogradeCondition(GameObjectHandle handle, ComponentHandle<MyselfMediatorComponent> mediator, unsigned int speed)
	:MyselfConditionBase(handle,mediator),
	speed_(speed)
{
}

MyselfRetrogradeCondition::~MyselfRetrogradeCondition()
{
}

void MyselfRetrogradeCondition::Update()
{
	//�X�V���̊֌W�ŁA�ʒu�E�p�x��߂���Ƃ�Mediator�ɂ���Ă��炤
}

unsigned int MyselfRetrogradeCondition::GetDamaged(unsigned int attack)
{
	//�������Ă��m�[�_��
	return 0;
}

bool MyselfRetrogradeCondition::IsShooterActive()
{
	return false;
}

void MyselfRetrogradeCondition::CheckHitComponent(std::set<ComponentHandle<CollisionComponent>>& hit_comps_)
{
	//�t�s�Đ����Ȃ̂ŉ������Ȃ�
}

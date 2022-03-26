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
	//更新順の関係で、位置・角度を戻す作業はMediatorにやってもらう
}

unsigned int MyselfRetrogradeCondition::GetDamaged(unsigned int attack)
{
	//何喰らってもノーダメ
	return 0;
}

bool MyselfRetrogradeCondition::IsShooterActive()
{
	return false;
}

void MyselfRetrogradeCondition::CheckHitComponent(std::set<ComponentHandle<CollisionComponent>>& hit_comps_)
{
	//逆行再生中なので何もしない
}

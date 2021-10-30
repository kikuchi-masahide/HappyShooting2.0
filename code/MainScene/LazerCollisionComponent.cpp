#include "LazerCollisionComponent.h"

LazerCollisionComponent::LazerCollisionComponent(GameObjectHandle obj, boost::shared_ptr<CollisionManager> manager)
	:CollisionComponent(obj,manager,150,CollisionManager::Tag::EnemyLazer,200)
{
	cupsule_ = CupsuleGeometry(This<CollisionComponent>());
}

LazerCollisionComponent::~LazerCollisionComponent()
{
}

void LazerCollisionComponent::Update()
{
	manager_->AddEnemyGeometry(&cupsule_);
}

void LazerCollisionComponent::CheckHitComponent()
{
}

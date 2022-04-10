#include "Boss2CollisionComponent.h"

#include "../Engine/GameObject.h"
#include "Boss2Mediator.h"

Boss2CollisionComponent::Boss2CollisionComponent(GameObjectHandle handle, boost::shared_ptr<CollisionManager> manager, ComponentHandle<Boss2MediatorComponent> med)
	:CollisionComponent(handle,manager,100,CollisionManager::Tag::EnemyBody,300),
	med_(med)
{
	circle_ = CircleGeometry(This<CollisionComponent>(), MatVec::Vector2(0, 0), 50.0);
}

Boss2CollisionComponent::~Boss2CollisionComponent()
{
}

void Boss2CollisionComponent::Update()
{
	circle_.center_ = mObj->GetPosition();
	manager_->AddEnemyGeometry(&circle_);
}

void Boss2CollisionComponent::CheckHitComponent()
{
	med_->CheckHitComponent(hit_comps_);
}

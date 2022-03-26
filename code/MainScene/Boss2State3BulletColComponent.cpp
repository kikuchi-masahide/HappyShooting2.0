#include "Boss2State3BulletColComponent.h"

#include "../Engine/GameObject.h"

Boss2State3BulletColComponent::Boss2State3BulletColComponent(GameObjectHandle obj, boost::shared_ptr<CollisionManager> manager)
	:CollisionComponent(obj,manager,50,CollisionManager::Tag::EnemyBullet,100),
	active_(true)
{
	circle_ = CircleGeometry(This<CollisionComponent>(), mObj->GetPosition(), radius_);
}

Boss2State3BulletColComponent::~Boss2State3BulletColComponent()
{
}

void Boss2State3BulletColComponent::Update()
{
	if (active_)
	{
		circle_.center_ = mObj->GetPosition();
		manager_->AddEnemyGeometry(&circle_);
	}
}

void Boss2State3BulletColComponent::CheckHitComponent()
{
	for (auto comp : hit_comps_)
	{
		if (comp->tag_ == CollisionManager::Tag::Myself)
		{
			active_ = false;
			break;
		}
	}
}

const double Boss2State3BulletColComponent::radius_ = 10.0;

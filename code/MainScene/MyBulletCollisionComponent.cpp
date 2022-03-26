#include "MyBulletCollisionComponent.h"

#include "CircleGeometry.h"
#include "MainScene.h"


MyBulletCollisionComponent::MyBulletCollisionComponent(GameObjectHandle obj, boost::shared_ptr<CollisionManager> manager, unsigned int damage, double radius)
	:CollisionComponent(obj, manager, 50, CollisionManager::Tag::MyBullet,damage),
	radius_(radius),active_(true)
{
	circle_ = CircleGeometry(This<CollisionComponent>(), mObj->GetPosition(), radius_);
}

MyBulletCollisionComponent::~MyBulletCollisionComponent()
{
}

void MyBulletCollisionComponent::Update()
{
	if(active_){
		circle_.center_ = mObj->GetPosition();
		manager_->AddFriendlyGeometry(&circle_);
	}
}

void MyBulletCollisionComponent::CheckHitComponent()
{
	for (auto comp : hit_comps_)
	{
		if (comp->tag_ == CollisionManager::Tag::EnemyBody)
		{
			//‰½‚©‚É“–‚½‚Á‚½‚±‚Æ‚ðŠo‚¦‚Ä‚¨‚­‚Ì‚Ý
			active_ = false;
			break;
		}
	}
}

#include "Enemy7BarrierCollisionComponent.h"

#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "LinearMoveComponent.h"
#include "DrawNormalBulletComponent.h"
#include "NormalBulletCollisionComponent.h"

Enemy7BarrierCollisionComponent::Enemy7BarrierCollisionComponent(GameObjectHandle handle, boost::shared_ptr<CollisionManager> col, boost::shared_ptr<LayerManager> layer)
	:CollisionComponent(handle, col, 100, CollisionManager::Tag::EnemyBody, 100),
	collision_(col), layer_(layer), health_(25000)
{
	circle_ = CircleGeometry(This<CollisionComponent>(), MatVec::Vector2(), 100);
}

Enemy7BarrierCollisionComponent::~Enemy7BarrierCollisionComponent()
{
}

void Enemy7BarrierCollisionComponent::Update()
{
	circle_.center_ = mObj->GetPosition();
	manager_->AddEnemyGeometry(&circle_);
}

void Enemy7BarrierCollisionComponent::CheckHitComponent()
{
	for (auto& comp : hit_comps_)
	{
		if (comp->tag_ == CollisionManager::Tag::MyBullet)
		{
			//Ž©‹@‚Ì’e‚ð”½ŽË‚µ‚ÄŽ©•ª‚Ì’e‚É‚·‚é
			InverseBullet(comp);
			
		}
		//“–‚½‚Á‚½•ªŽ©•ª‚Ìƒwƒ‹ƒX‚àŒ¸‚ç‚·
		health_ -= min(health_, comp->GetDamage());
	}
	if (health_ == 0)
	{
		mObj->SetDeleteFlag();
	}
}

double Enemy7BarrierCollisionComponent::GetHealthRate()
{
	return (double)health_ / 25000;
}

void Enemy7BarrierCollisionComponent::InverseBullet(ComponentHandle<CollisionComponent> comp)
{
	//TODO:Ž©‹@’e‚Ì”ò‚ñ‚Å‚­•ûŒü = ‚»‚ÌƒIƒuƒWƒFƒNƒg‚Ìrotation(????????)
	auto posdif = comp->mObj->GetPosition() - mObj->GetPosition();
	//ƒoƒŠƒA‚Ì’†S‚©‚ç’e‚Ö‚ÌƒxƒNƒgƒ‹‚Ì‚È‚·Šp
	auto theta = atan2(posdif(1), posdif(0));
	//’e‚Ì”ò‚ñ‚Ås‚Á‚Ä‚¢‚½•ûŒü
	auto d = comp->mObj->GetRotation();
	//V‚µ‚¢’e‚Ì”ò‚ñ‚Å‚¢‚­•ûŒü
	auto to = 2 * theta - d - PI;
	auto obj = mObj->mScene->AddObject(comp->mObj->GetPosition(), 1.0, 0.0);
	obj->AddUpdateComponent<LinearMoveComponent>(MatVec::Vector2(cos(to), sin(to)) * 50.0 / 6, 7.0);
	obj->AddOutputComponent<DrawNormalBulletComponent>(layer_, 7.0, MatVec::Vector3(1.0, 0.0, 0.0), 1.0, -10.0);
	obj->AddUpdateComponent<NormalBulletCollisionComponent>(7.0, 100, collision_);
	//Œ³‚Ì’e‚ÍÁ‚·
	comp->mObj->SetDeleteFlag();
}

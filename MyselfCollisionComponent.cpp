#include "stdafx.h"
#include "MyselfCollisionComponent.h"

#include "MyselfMediatorComponent.h"
#include "GameObject.h"

#include "MainScene.h"

MyselfCollisionComponent::MyselfCollisionComponent(GameObjectHandle myself, boost::shared_ptr<CollisionManager> manager, ComponentHandle<MyselfMediatorComponent> mediator)
	:CollisionComponent(myself, manager, 75,CollisionManager::Tag::Myself,damage_),
	geometry_(This<CollisionComponent>(), myself->GetPosition(),circle_radius_),mediator_(mediator)
{
}

MyselfCollisionComponent::~MyselfCollisionComponent()
{
}

void MyselfCollisionComponent::Update()
{
	//‰~‚ÌˆÊ’uXV
	geometry_.center_ = mObj->GetPosition();
	manager_->AddCircleGeometry(&geometry_);
}

void MyselfCollisionComponent::CheckHitComponent()
{
	if (hit_comps_.size() == 0)return;
	//Ž©‹@‚ªƒ_ƒ[ƒW‚ð‹ò‚ç‚í‚È‚¢ó‘Ô‚È‚ç‚ÎC’e‚É“–‚½‚Á‚Ä‚¢‚Ä‚àŒ©‚È‚¢
	if (mediator_->IsInvincible())return;
	//Žn‚ß‚ÌˆêŒ‚‚Ì‚Ý‚ðŠ¨ˆÄ‚·‚é
	auto comp = *(hit_comps_.begin());
	//“G‹@‚Æ“–‚½‚Á‚½ê‡
	if (comp->tag_ == CollisionManager::Tag::EnemyBody)
	{
		mediator_->CauseDamageToMyself(comp->GetDamage());
	}
	//“G’e‚Æ“–‚½‚Á‚½ê‡
	if (comp->tag_ == CollisionManager::Tag::EnemyBullet)
	{
		mediator_->CauseDamageToMyself(comp->GetDamage());
		comp->SetDeleteFlag();
	}
}

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
	//円の位置更新
	geometry_.center_ = mObj->GetPosition();
	manager_->AddCircleGeometry(&geometry_);
}

void MyselfCollisionComponent::CheckHitComponent()
{
	if (hit_comps_.size() == 0)return;
	//自機がダメージを喰らわない状態ならば，弾に当たっていても見ない
	if (mediator_->IsInvincible())return;
	//始めの一撃のみを勘案する
	auto comp = *(hit_comps_.begin());
	//敵機またはレーザーと当たった場合
	if (comp->tag_ == CollisionManager::Tag::EnemyBody || comp->tag_ == CollisionManager::Tag::EnemyLazer)
	{
		mediator_->CauseDamageToMyself(comp->GetDamage());
	}
	//敵弾と当たった場合
	if (comp->tag_ == CollisionManager::Tag::EnemyBullet)
	{
		mediator_->CauseDamageToMyself(comp->GetDamage());
		comp->mObj->SetDeleteFlag();
	}
}

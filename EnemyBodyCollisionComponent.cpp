#include "stdafx.h"
#include "EnemyBodyCollisionComponent.h"

#include "EnemyHealthComponent.h"
#include "ScoreManager.h"

EnemyBodyCollisionComponent::EnemyBodyCollisionComponent(GameObjectHandle object, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<ScoreManager> score_manager, ComponentHandle<EnemyHealthComponent> health, unsigned int damage, int upd_priority)
	:CollisionComponent(object, collision_manager, upd_priority, CollisionManager::Tag::EnemyBody,damage),
	health_component_(health),score_manager_(score_manager)
{
}

EnemyBodyCollisionComponent::~EnemyBodyCollisionComponent()
{
}

void EnemyBodyCollisionComponent::CheckHitComponent()
{
	for (auto comp : hit_comps_)
	{
		//Ž©‹@‚Ü‚½‚ÍŽ©‹@’e‚Æ‚ÌÕ“Ë
		if (comp->tag_ == CollisionManager::Tag::Myself || comp->tag_ == CollisionManager::Tag::MyBullet)
		{
			auto damage = comp->GetDamage();
			auto real_damage = health_component_->Damage(damage);
			score_manager_->AddScore(real_damage);
		}
	}
}

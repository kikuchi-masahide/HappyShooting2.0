#include "stdafx.h"
#include "EnemyHealthComponent.h"
#include "DrawDeathEffectComponent.h"

#include "LayerManager.h"
#include "Scene.h"

EnemyHealthComponent::EnemyHealthComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer_manager, double health0)
	:Component(handle,50),health_(health0),layer_manager_(layer_manager),all_health_(health0)
{
}

EnemyHealthComponent::~EnemyHealthComponent()
{
}

double EnemyHealthComponent::Damage(double damage)
{
	double real_damage = min(health_, damage);
	health_ -= real_damage;
	if (health_ <= 0)
	{
		mObj->SetDeleteFlag();
		auto death_effect = mObj->mScene->AddObject(mObj->GetPosition(), 1.0, 0.0);
		death_effect->AddOutputComponent<DrawDeathEffectComponent>(layer_manager_,-9.0);
	}
	return real_damage;
}

void EnemyHealthComponent::Update()
{
}

double EnemyHealthComponent::GetHealthRate()
{
	return health_ / all_health_;
}

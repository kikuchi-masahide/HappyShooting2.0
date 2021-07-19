#include "stdafx.h"
#include "EnemyHealthComponent.h"
#include "DrawDeathEffectComponent.h"

#include "MainScene.h"

EnemyHealthComponent::EnemyHealthComponent(GameObjectHandle handle, MainScene* scene, double health0)
	:Component(handle,50),health_(health0),scene_(scene)
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
		auto death_effect = scene_->AddObject(mObj->GetPosition(), 1.0, 0.0);
		death_effect->AddOutputComponent<DrawDeathEffectComponent>(scene_->GetLayerManager());
	}
	return real_damage;
}

void EnemyHealthComponent::Update()
{
}

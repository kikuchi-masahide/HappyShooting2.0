#include "stdafx.h"
#include "EnemyHealthComponent.h"

#include "MainScene.h"

EnemyHealthComponent::EnemyHealthComponent(MainScene* scene, GameObjectHandle object, double health0)
	:Component(50),health_(health0),scene_(scene),object_(object)
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
		object_->SetDeleteFlag();
		// TODO:消滅エフェクトの追加
	}
	return real_damage;
}

void EnemyHealthComponent::Update()
{
}

#include "stdafx.h"
#include "EnemyHealthComponent.h"

#include "MainScene.h"

EnemyHealthComponent::EnemyHealthComponent(MainScene* scene, GameObjectHandle object, double health0)
	:Component(50),health_(health0),scene_(scene)
{
}

EnemyHealthComponent::~EnemyHealthComponent()
{
}

void EnemyHealthComponent::Damage(double damage)
{
	health_ -= damage;
}

void EnemyHealthComponent::Update()
{
	if (health_ <= 0)
	{
		object_->SetDeleteFlag();
		// TODO:消滅エフェクトの追加
	}
}

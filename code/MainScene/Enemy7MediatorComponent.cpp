#include "Enemy7MediatorComponent.h"

#include "DrawTextureComponent.h"
#include "LayerManager.h"
#include "../Engine/Scene.h"
#include "LinearMoveComponent.h"
#include "DrawNormalBulletComponent.h"
#include "NormalBulletCollisionComponent.h"
#include "EnemyHealthComponent.h"
#include "Enemy7CollisionComponent.h"
#include "ScoreManager.h"
#include "DrawHealthBarComponent.h"

Enemy7MediatorComponent::Enemy7MediatorComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col, boost::shared_ptr<ScoreManager> score)
	:Component(handle),
	time_(-240),layer_(layer),collision_(col)
{
	texture_ = mObj->AddOutputComponent<DrawTextureComponent>(layer, 28, -5.0);
	texture_->width_ = 50.0;
	texture_->height_ = 50.0;
	texture_->alpha_ = 1.0;
	auto health = mObj->AddUpdateComponent<EnemyHealthComponent>(layer_, health0_);
	mObj->AddUpdateComponent<Enemy7CollisionComponent>(collision_, score, health);
	mObj->AddOutputComponent<DrawHealthBarComponent<EnemyHealthComponent>>(layer_, health, MatVec::Vector2(0, 30));
}

Enemy7MediatorComponent::~Enemy7MediatorComponent()
{
}

void Enemy7MediatorComponent::Update()
{
	auto pos = mObj->GetPosition();
	if (time_ < 0)
	{
		pos(0) = 0.0;
		pos(1) = 400.0-5.0*time_/6;
	}
	else {
		pos(0) = 100.0 * sin(PI * time_ / 240);
		pos(1) = 400.0;
	}
	mObj->SetPosition(pos);
	mObj->SetRotation(PI * time_ / 240);
	if (time_ >= 0 && time_%12 == 0)
	{
		Shoot();
	}
	time_++;
}

void Enemy7MediatorComponent::Shoot()
{
	auto pos = mObj->GetPosition();
	//Ž©•ª‚ÌŒü‚¢‚Ä‚é•ûŒü
	auto deg0 = mObj->GetRotation();
	for (int d = 0; d < 4; d++)
	{
		//’e‚ðŒ‚‚Â•ûŒü
		auto deg = deg0 + PI * d / 2;
		auto obj = mObj->mScene->AddObject(pos, 1.0, deg + PI*d/2);
		obj->AddUpdateComponent<LinearMoveComponent>(MatVec::Vector2(cos(deg), sin(deg)) * 2.0, 10.0);
		obj->AddOutputComponent<DrawNormalBulletComponent>(layer_, 10.0, MatVec::Vector3(0.0, 1.0, 0.0), 1.0, -10.0);
		obj->AddUpdateComponent<NormalBulletCollisionComponent>(10.0, 100, collision_);
	}
}

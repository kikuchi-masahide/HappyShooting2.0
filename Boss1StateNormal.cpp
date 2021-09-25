#include "stdafx.h"
#include "Boss1StateNormal.h"

#include "Boss1MediatorComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "LinearMoveComponent.h"
#include "DrawTextureComponent.h"


Boss1StateNormal::Boss1StateNormal(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager)
	:Boss1StateBase(mediator,layer_manager,score_manager,collision_manager),
	counter_(0),deg_(0.0)
{
}

Boss1StateNormal::~Boss1StateNormal()
{
}

void Boss1StateNormal::Update()
{
	//’e‚ðŒ‚‚Âtick
	if (counter_ % bullet_period_ == 0)
	{
		AddBullet();
	}
	if (counter_ == mode_period_ - 1)
	{
		mediator_->ChangeState(nullptr);
	}
	counter_++;
}

void Boss1StateNormal::AddBullet()
{
	auto obj = mediator_->mObj;
	auto objpos = obj->GetPosition();
	double deg = deg_;
	double delta = 2 * PI / bullet_num_;
	for (int n = 0; n < bullet_num_; n++)
	{
		auto bullet = obj->mScene->AddObject(objpos, 1.0, deg);
		bullet->AddUpdateComponent<LinearMoveComponent>(MatVec::Vector2(cos(deg), sin(deg)) * bullet_speed_, 20.0);
		auto texture = bullet->AddOutputComponent<DrawTextureComponent>(layer_manager_, 19, -10.0);
		texture->alpha_ = 1.0;
		texture->width_ = 20.0;
		texture->height_ = 20.0;
		deg += delta;
	}
}

#include "stdafx.h"
#include "Boss1StateNormal.h"

#include "Boss1MediatorComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "LinearMoveComponent.h"
#include "DrawTextureComponent.h"


Boss1StateNormal::Boss1StateNormal(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager)
	:Boss1StateBase(mediator,layer_manager,score_manager,collision_manager),
	counter_(0),deg_(0.0),configured_(-1)
{
	next_bullet_.resize(bullet_num_);
	bullet_texture_.resize(bullet_num_);
}

Boss1StateNormal::~Boss1StateNormal()
{
}

void Boss1StateNormal::Update()
{
	//’e‚ðŒ‚‚Âtick
	if (counter_ > 0 && counter_ % bullet_period_ == 0)
	{
		double deg = deg_;
		double delta = 2 * PI / bullet_num_;
		for (int n = 0; n < bullet_num_; n++)
		{
			bullet_texture_[n]->width_ = 20.0;
			bullet_texture_[n]->height_ = 20.0;
			next_bullet_[n]->AddUpdateComponent<LinearMoveComponent>(MatVec::Vector2(cos(deg), sin(deg)) * bullet_speed_, 20.0);
			deg += delta;
		}
		configured_ = -1;
		auto& profiler = mediator_->mObj->mScene->mGame.profiler_;
		profiler.SetRecordName("add_bullet");
	}
	else {
		//TODO:96ŒÂ‚Ì’e‚ð’Ç‰Á‚·‚é‚Æ(Žå‚ÉCreateConstBuffer‚Ìˆ—‚ª)d‚¢‚Ì‚ÅC1tick‚É‚Â‚«4ŒÂ‚¸‚Â’e‚ð’Ç‰Á‚µ‚Ä‚¨‚­‚±‚Æ‚É‚·‚é
		auto obj = mediator_->mObj;
		auto objpos = obj->GetPosition();
		double delta = 2 * PI / bullet_num_;
		for (int n = 1; n <= 4; n++)
		{
			configured_++;
			if (configured_ >= bullet_num_)
			{
				break;
			}
			double deg = deg_+delta*configured_;
			next_bullet_[configured_] = obj->mScene->AddObject(objpos, 1.0, deg);
			bullet_texture_[configured_] = next_bullet_[configured_]->AddOutputComponent<DrawTextureComponent>(layer_manager_, 19, -10.0);
			bullet_texture_[configured_]->alpha_ = 1.0;
		}
	}
	if (counter_ == mode_period_ - 1)
	{
		mediator_->ChangeState(nullptr);
	}
	counter_++;
}

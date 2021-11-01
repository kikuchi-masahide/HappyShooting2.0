#include "Boss1State1.h"

#include "Boss1MediatorComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "Boss1StateNormal.h"
#include "Boss1State1MasterBullet.h"

Boss1State1::Boss1State1(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager)
	:Boss1StateBase(mediator,layer_manager,score_manager,collision_manager),
	counter_(0)
{
}

Boss1State1::~Boss1State1()
{
}

void Boss1State1::Update()
{
	if (counter_ == launch_counter_first_)
	{
		AddMasterBullet(popup_centerx_);
	}
	else if (counter_ == launch_counter_second_)
	{
		AddMasterBullet(popup_leftx_);
		AddMasterBullet(popup_rightx_);
	}
	else if (counter_ == launch_counter_third_)
	{
		AddMasterBullet(popup_leftx_);
		AddMasterBullet(popup_centerx_);
		AddMasterBullet(popup_rightx_);
	}
	else if (counter_ == terminal_counter_)
	{
		mediator_->ChangeState(new Boss1StateNormal(mediator_, layer_manager_, score_manager_, collision_manager_, 2));
	}
	counter_++;
}

bool Boss1State1::IsCollisionActive()
{
	return true;
}

void Boss1State1::AddMasterBullet(double x)
{
	auto bullet = mediator_->mObj->mScene->AddObject(MatVec::Vector2(), 1.0, 0.0);
	bullet->AddUpdateComponent<Boss1State1MasterBullet>(x,layer_manager_,score_manager_,collision_manager_);
}

#include "Boss1State3.h"

#include "Boss1MediatorComponent.h"
#include "Boss1StateNormal.h"
#include "EnemyWaveManager.h"
#include "../Engine/Scene.h"
#include "LinearMoveComponent.h"
#include "DrawNormalBulletComponent.h"
#include "NormalBulletCollisionComponent.h"
#include "MyselfPosAdjustComponent.h"
#include "LayerManager.h"

Boss1State3::Boss1State3(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager)
	:Boss1StateBase(mediator,layer_manager,score_manager,collision_manager,enemywave_manager),
	counter_(counter_initial_)
{
	auto myself = enemywave_manager_->GetMyselfHandle();
	auto obj = mediator_->mObj;
	pos_adjust_[0] = obj->AddUpdateComponent<MyselfPosAdjustComponent>(myself, MatVec::Vector2(-300.0, -450.0), MatVec::Vector2(-300.0, +450.0));
	pos_adjust_[1] = obj->AddUpdateComponent<MyselfPosAdjustComponent>(myself, MatVec::Vector2(-300.0, +450.0), MatVec::Vector2(+300.0, +450.0));
	pos_adjust_[2] = obj->AddUpdateComponent<MyselfPosAdjustComponent>(myself, MatVec::Vector2(+300.0, +450.0), MatVec::Vector2(+300.0, -450.0));
	pos_adjust_[3] = obj->AddUpdateComponent<MyselfPosAdjustComponent>(myself, MatVec::Vector2(+300.0, -450.0), MatVec::Vector2(-300.0, -450.0));
}

Boss1State3::~Boss1State3()
{
	for (int n = 0; n < 4; n++) {
		if (pos_adjust_[n].IsValid())
		{
			pos_adjust_[n]->SetDeleteFlag();
		}
	}
	layer_manager_->SwapLayer(0);
}

void Boss1State3::Update()
{
	//counter_‚ª•‰‚ÌŽž‚Í‘Ò‹@
	if (counter_ < 0)
	{
		counter_++;
		//ŽŸUpdate‚©‚ç•`‰æ‚ð‹·‚ß‚Ä‚¢‚­‚Ì‚Å
		if (counter_ == 0)
		{
			layer_manager_->SwapLayer(2);
		}
		return;
	}
	//n•b+0,3,6,...,30tick(n=0,...,launch_repeat_time_-1)‚Ìƒ^ƒCƒ~ƒ“ƒO‚Å’e‚ðŒ‚‚Â
	if (counter_ < 60 * launch_repeat_time_) {
		int counter_mod_60 = counter_ % 60;
		if (counter_mod_60 % 3 == 0 && counter_mod_60 <= 30)
		{
			AddBullet();
		}
	}
	//Ž©‹@ˆÚ“®§ŒÀ
	double rotate;
	double expand;
	if (counter_ < shrink_period_)
	{
		rotate = max_rotate_angle_ * counter_ / shrink_period_;
		expand = (1.0 * (shrink_period_ - counter_) + max_expand_ratio_ * counter_) / shrink_period_;
	}
	else if (counter_ < whole_period_ + 1 - shrink_period_)
	{
		rotate = max_rotate_angle_;
		expand = max_expand_ratio_;
	}
	else {
		int c = whole_period_ + 1 - counter_;
		rotate = max_rotate_angle_ * c / shrink_period_;
		expand = (1.0 * (shrink_period_ - c) + max_expand_ratio_ * c) / shrink_period_;
	}
	//pos_adjust_[n]‚Íanchor[n]‚ða_Canchor[n+1]‚ðb_‚Æ‚·‚é
	MatVec::Vector2 anchor[5];
	anchor[0] = MatVec::Vector2(-300.0, -450.0);
	anchor[1] = MatVec::Vector2(-300.0, +450.0);
	anchor[2] = MatVec::Vector2(+300.0, +450.0);
	anchor[3] = MatVec::Vector2(+300.0, -450.0);
	anchor[4] = MatVec::Vector2(-300.0, -450.0);
	//anchor‚ð‰ñ“]CŠg‘åk¬‚³‚¹‚é
	for (int n = 0; n < 5; n++)
	{
		anchor[n] *= expand;
		double x = anchor[n](0);
		double y = anchor[n](1);
		anchor[n] = MatVec::Vector2(x * cos(rotate) - y * sin(rotate), x * sin(rotate) + y * cos(rotate));
	}
	for (int n = 0; n < 4; n++)
	{
		pos_adjust_[n]->SetAnchorPoint(anchor[n], anchor[n + 1]);
	}
	//‚±‚Ìƒ‚[ƒhI—¹
	if (counter_ == whole_period_)
	{
		mediator_->ChangeState(DBG_NEW Boss1StateNormal(mediator_, layer_manager_, score_manager_, collision_manager_, enemywave_manager_, 1));
	}
	counter_++;
}

bool Boss1State3::IsCollisionActive()
{
	return true;
}

void Boss1State3::AddBullet()
{
	auto myself_pos = enemywave_manager_->GetMyselfHandle()->GetPosition();
	myself_pos -= mediator_->mObj->GetPosition();
	double theta0 = atan2(myself_pos(1), myself_pos(0)) - ball_angle_dif_;
	for (unsigned int n = 0; n < 3; n++)
	{
		//‚±‚Ì•ûŒü‚É’e‚ð”ò‚Î‚·
		double theta = theta0 + ball_angle_dif_ * n;
		auto obj = mediator_->mObj->mScene->AddObject(mediator_->mObj->GetPosition(), 1.0, theta);
		obj->AddUpdateComponent<LinearMoveComponent>(MatVec::Vector2(cos(theta), sin(theta)) * ball_speed_, ball_size_);
		obj->AddOutputComponent<DrawNormalBulletComponent>(layer_manager_, ball_size_, MatVec::Vector3(1.0, 0.0, 0.0), 1.0, -10.0);
		obj->AddUpdateComponent<NormalBulletCollisionComponent>(ball_size_, 100.0, collision_manager_);
	}
}

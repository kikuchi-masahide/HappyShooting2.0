#include "Boss2State2.h"

#include "Boss2Mediator.h"
#include "../Engine/GameObject.h"
#include "Boss2State0.h"
#include "../Engine/Scene.h"
#include "Boss2State2Bullet.h"

Boss2State2::Boss2State2(ComponentHandle<Boss2MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager)
	:Boss2StateBase(mediator,layer_manager,score_manager,collision_manager,enemywave_manager),
	time_(0)
{
}

Boss2State2::~Boss2State2()
{
}

void Boss2State2::Update()
{
	//timetable_[n].time_ < time_ <= timetable_[n+1].time_
	int n = 15;
	while (timetable_[n].time_ >= time_)
	{
		n--;
	}
	//üŒ`•âŠ®
	int tn = timetable_[n].time_;
	int tnn = timetable_[n + 1].time_;
	auto pn = timetable_[n].pos_;
	auto pnn = timetable_[n+1].pos_;
	auto pos = (1.0 - (double)(time_ - tn) / (tnn - tn)) * pn + (double)(time_ - tn) / (tnn - tn) * pnn;
	mediator_->mObj->SetPosition(pos);
	//ƒJƒx‚ÉÕ“Ë‚µ‚½
	if (abs(pos(0)) >= 300.0 - 50.0 || abs(pos(1)) >= 450.0 - 50.0)
	{
		Shoot();
	}
	time_++;
	if (time_ == state_duration_)
	{
		mediator_->ChangeState(boost::shared_ptr<Boss2State0>(new Boss2State0(
			mediator_, layer_manager_, score_manager_, collision_manager_, enemywave_manager_
		)));
	}
}

bool Boss2State2::IsCollisionActive()
{
	return true;
}

bool Boss2State2::IsInvincible()
{
	return false;
}

void Boss2State2::Shoot()
{
	auto pos = mediator_->mObj->GetPosition();
	auto scene = mediator_->mObj->mScene;
	for (int n = 0; n < bullet_num_; n++)
	{
		double deg = 2 * PI * n / bullet_num_;
		auto obj = scene->AddObject(pos, 1.0, 0.0);
		obj->AddUpdateComponent<Boss2State2Bullet>(deg, layer_manager_, collision_manager_);
	}
}

const Boss2State2TimeTable Boss2State2::timetable_[16] = {
	Boss2State2TimeTable(-1,MatVec::Vector2(0.0,390.0)),
	Boss2State2TimeTable(60,MatVec::Vector2(0.0,390.0)),
	Boss2State2TimeTable(60 + 24 * 1,MatVec::Vector2(-100.0,-450.0 + 50.0)),
	Boss2State2TimeTable(60 + 24 * 2,MatVec::Vector2(300.0 - 50.0,150.0)),
	Boss2State2TimeTable(60 + 24 * 3,MatVec::Vector2(-300.0 + 50.0,150.0)),
	Boss2State2TimeTable(60 + 24 * 4,MatVec::Vector2(100.0,-450.0 + 50.0)),
	Boss2State2TimeTable(60 + 24 * 5,MatVec::Vector2(0.0,450.0 - 50.0)),
	Boss2State2TimeTable(210,MatVec::Vector2(0.0,390.0)),
	Boss2State2TimeTable(300,MatVec::Vector2(0.0,390.0)),
	Boss2State2TimeTable(300 + 24 * 1,MatVec::Vector2(100.0,-450.0 + 50.0)),
	Boss2State2TimeTable(300 + 24 * 2,MatVec::Vector2(-300.0 + 50.0,150.0)),
	Boss2State2TimeTable(300 + 24 * 3,MatVec::Vector2(300.0 - 50.0,150.0)),
	Boss2State2TimeTable(300 + 24 * 4,MatVec::Vector2(-100.0,-450.0 + 50.0)),
	Boss2State2TimeTable(300 + 24 * 5,MatVec::Vector2(0.0,450.0 - 50.0)),
	Boss2State2TimeTable(450,MatVec::Vector2(0.0,390.0)),
	Boss2State2TimeTable(600,MatVec::Vector2(0.0,390.0)),
};
const int Boss2State2::state_duration_ = 600;
const int Boss2State2::bullet_num_ = 16;

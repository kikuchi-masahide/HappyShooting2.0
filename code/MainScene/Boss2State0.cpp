#include "Boss2State0.h"

#include "../Engine/Math/Math.h"
#include "Boss2Mediator.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "Boss2State0BulletBig.h"
#include "Boss2State1.h"

//TODO:大きい弾がちょっと画面外に出た時、全体の描画がキャンセルされてチカチカしてるっぽい

Boss2State0::Boss2State0(ComponentHandle<Boss2MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager)
	:Boss2StateBase(mediator,layer_manager,score_manager,collision_manager,enemywave_manager),
	time_(0)
{
}

Boss2State0::~Boss2State0()
{
}

void Boss2State0::Update()
{
	//でっかい弾生成
	if (time_ % bullet_period_ == 0 && time_ < bullet_repeat_ * bullet_period_)
	{
		auto bullet = mediator_->mObj->mScene->AddObject(MatVec::Vector2(),1.0,0.0);
		//初期化、更新は全部任せる
		if ((time_ / bullet_period_) % 2 == 0) {
			bullet->AddUpdateComponent<Boss2State0BulletBig>(false, layer_manager_, collision_manager_);		
		}
		else {
			bullet->AddUpdateComponent<Boss2State0BulletBig>(true, layer_manager_, collision_manager_);
		}
	}
	time_++;
	if (time_ == whole_duration_)
	{
		mediator_->ChangeState(boost::shared_ptr<Boss2State1>(DBG_NEW Boss2State1(
			mediator_, layer_manager_, score_manager_, collision_manager_, enemywave_manager_
		)));
	}
}

const int Boss2State0::bullet_period_ = 60;
const int Boss2State0::bullet_repeat_ = 16;
const int Boss2State0::whole_duration_ = 1200;

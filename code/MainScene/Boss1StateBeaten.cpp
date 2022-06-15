#include "Boss1StateBeaten.h"

#include "Boss1MediatorComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "DrawDeathEffectComponent.h"
#include "EnemyWaveManager.h"
#include "MainScene.h"

Boss1StateBeaten::Boss1StateBeaten(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager)
	:Boss1StateBase(mediator,layer_manager,score_manager,collision_manager,enemywave_manager),
	counter_(0),rand_dev_(),def_rand_eng_(rand_dev_()),dist_(-1.0,1.0)
{
	mediator_->PauseAnimation(true);
}

Boss1StateBeaten::~Boss1StateBeaten()
{
}

void Boss1StateBeaten::Update()
{
	if (counter_ == 120)
	{
		auto pos = mediator_->mObj->GetPosition();
		AddDeathEffect(pos, 500);
		mediator_->mObj->SetDeleteFlag();
		enemywave_manager_->scene_->SetMyselfArmor2();
		enemywave_manager_->scene_->AddLife(2);
		return;
	}
	if (counter_ % 6 == 0)
	{
		auto pos = mediator_->mObj->GetPosition();
		double x = dist_(def_rand_eng_);
		double y = dist_(def_rand_eng_);
		AddDeathEffect(pos + MatVec::Vector2(x, y) * 100.0);
	}
	counter_++;
}

bool Boss1StateBeaten::IsCollisionActive()
{
	return false;
}

bool Boss1StateBeaten::IsInvincible()
{
	return true;
}

void Boss1StateBeaten::AddDeathEffect(MatVec::Vector2 pos, double radius)
{
	auto obj = mediator_->mObj->mScene->AddObject(pos, 1.0, 0.0);
	obj->AddOutputComponent<DrawDeathEffectComponent>(layer_manager_, 20.0, radius);
}

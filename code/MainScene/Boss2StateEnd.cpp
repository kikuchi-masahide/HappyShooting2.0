#include "Boss2StateEnd.h"

#include "../Engine/GameObject.h"
#include "Boss2Mediator.h"
#include "DrawDeathEffectComponent.h"
#include "../Engine/Scene.h"
#include "CollisionComponent.h"
#include "LayerManager.h"
#include "GameClearUI.h"

Boss2StateEnd::Boss2StateEnd(ComponentHandle<Boss2MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager)
	:Boss2StateBase(mediator, layer_manager, score_manager, collision_manager, enemywave_manager),
	time_(0),layer_manager_(layer_manager)
{
	//考えるのだるいんでもう瞬間移動させる
	mediator_->mObj->SetPosition(MatVec::Vector2(0.0, 390.0));
}

Boss2StateEnd::~Boss2StateEnd()
{
}

void Boss2StateEnd::Update()
{
	time_++;
	if (time_ == 240)
	{
		//最後に派手に爆発して消滅
		auto obj = mediator_->mObj->mScene->AddObject(MatVec::Vector2(0.0, 390.0), 1.0, 0.0);
		obj->AddOutputComponent<DrawDeathEffectComponent>(layer_manager_, 20.0, 600.0);
		layer_manager_->SwapLayer(5);
	}
	else if (time_ == 255)
	{
		mediator_->HaltDrawing();
	}
	else if (time_ == 270)
	{
		mediator_->mObj->mScene->AddUIScreen<GameClearUI>();
	}
	else if (time_ == 390)
	{
		layer_manager_->SwapLayer(0);
		mediator_->mObj->SetDeleteFlag();
	}
}

int Boss2StateEnd::CheckHitComponents(std::set<ComponentHandle<CollisionComponent>>& hit_comps)
{
	if (time_ > 240)
	{
		return 0;
	}
	//弾が当たったところに小爆発を起こす
	for (auto& comp : hit_comps)
	{
		if (comp->tag_ != CollisionManager::Tag::MyBullet)
		{
			continue;
		}
		auto pos = comp->mObj->GetPosition();
		auto obj = mediator_->mObj->mScene->AddObject(pos, 1.0, 0.0);
		obj->AddOutputComponent<DrawDeathEffectComponent>(layer_manager_);
	}
	return 0;
}



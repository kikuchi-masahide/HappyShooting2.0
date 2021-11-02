#include "EnemyWaveBase.h"

#include "Math.h"
#include "../Engine/GameObject.h"
#include "EnemyWaveManager.h"
#include "MainScene.h"

EnemyWaveBase::EnemyWaveBase(unsigned int tick_after_clear, MainScene* main_scene)
	:tick_after_clear_(tick_after_clear), counter_(-1), main_scene_(main_scene)
{
	myself_handle_ = main_scene_->GetMyselfHandle();
}

EnemyWaveBase::~EnemyWaveBase()
{
}

void EnemyWaveBase::Update()
{
	if (counter_ == -1) {
		auto itr = enemies_.begin();
		while (itr != enemies_.end())
		{
			if (!itr->IsValid())
			{
				itr = enemies_.erase(itr);
			}
			else {
				itr++;
			}
		}
		if (enemies_.size() == 0)
		{
			counter_ = 0;
		}
	}
	if (counter_ != -1) {
		if (counter_ == tick_after_clear_)
		{
			OnDelete();
			return;
		}
		counter_++;
	}
}

GameObjectHandle EnemyWaveBase::SolveNearestEnemy()
{
	GameObjectHandle nearest;
	double min_dist = 1e8;
	MatVec::Vector2 mypos = myself_handle_->GetPosition();
	for (auto itr = enemies_.begin();itr != enemies_.end();itr++)
	{
		MatVec::Vector2 enemy_pos = (*itr)->GetPosition();
		double dist = (enemy_pos - mypos).Norm();
		if (min_dist > dist)
		{
			min_dist = dist;
			nearest = *itr;
		}
	}
	return nearest;
}

void EnemyWaveBase::AddEnemy(GameObjectHandle object)
{
	enemies_.push_back(object);
}

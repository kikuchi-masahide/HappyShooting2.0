#include "EnemyWaveManager.h"

#include "MainScene.h"
#include "EnemyWaveBase.h"
#include "EnemyWave1.h"

#include "EnemyWaveBoss1.h"

#include "EnemyWave45.h"

EnemyWaveManager::EnemyWaveManager(MainScene* scene)
	:scene_(scene), counter_(-1)
{
}

EnemyWaveManager::~EnemyWaveManager()
{
	if (wave_)
	{
		//Manager��Wave�����ꂼ���boost::shared_ptr�Ŏ����Ă���̂ŁC
		wave_.reset();
	}
}

void EnemyWaveManager::SetWave(boost::shared_ptr<EnemyWaveBase> wave)
{
	wave_ = wave;
	counter_ = -1;
}

GameObjectHandle EnemyWaveManager::SolveNearestEnemy()
{
	GameObjectHandle nearest;
	double min_dist = 1e8;
	auto myself_handle_ = scene_->GetMyselfHandle();
	MatVec::Vector2 mypos = myself_handle_->GetPosition();
	for (auto itr = enemies_.begin(); itr != enemies_.end(); itr++)
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

void EnemyWaveManager::Update()
{
	if (!wave_)
	{
		return;
	}
	//�Otick�ł͑S�ł��Ă��Ȃ������ꍇ
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
	//����tick�őS�ł��m�F�����A���邢�͑O����S�ł��Ă����ꍇ
	if (counter_ != -1) {
		if (counter_ == wave_->tick_after_clear_)
		{
			wave_->OnDelete();
			return;
		}
		counter_++;
	}
}

GameObjectHandle EnemyWaveManager::GetMyselfHandle()
{
	return scene_->GetMyselfHandle();
}

void EnemyWaveManager::AddEnemyInWave(GameObjectHandle enemy)
{
	enemies_.push_back(enemy);
}

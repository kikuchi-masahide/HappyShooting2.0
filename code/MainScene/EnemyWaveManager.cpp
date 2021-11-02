#include "EnemyWaveManager.h"

#include "MainScene.h"
#include "EnemyWaveBase.h"
#include "EnemyWave1.h"

#include "EnemyWaveBoss1.h"

#include "EnemyWave45.h"

EnemyWaveManager::EnemyWaveManager(MainScene* scene)
	:scene_(scene),has_switched_(false)
{
}

EnemyWaveManager::~EnemyWaveManager()
{
	if (wave_)
	{
		//ManagerとWaveがそれぞれをboost::shared_ptrで持っているので，
		wave_.reset();
	}
	if (next_wave_)
	{
		next_wave_.reset();
	}
}

void EnemyWaveManager::SetWave(boost::shared_ptr<EnemyWaveBase> wave)
{
	//wave_自体の更新は，この関数が終わった後に行う
	next_wave_ = wave;
	//フラグを立てておく
	has_switched_ = true;
}

GameObjectHandle EnemyWaveManager::SolveNearestEnemy()
{
	return wave_->SolveNearestEnemy();
}

void EnemyWaveManager::Update()
{
	if (wave_ != nullptr) {
		wave_->Update();
	}
	if (has_switched_) {
		wave_ = next_wave_;
		next_wave_ = nullptr;
		has_switched_ = false;
	}
}

GameObjectHandle EnemyWaveManager::GetMyselfHandle()
{
	return scene_->GetMyselfHandle();
}

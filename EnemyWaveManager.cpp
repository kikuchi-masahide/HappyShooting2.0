#include "stdafx.h"
#include "EnemyWaveManager.h"

#include "MainScene.h"
#include "EnemyWaveBase.h"
#include "EnemyWave1.h"

#include "EnemyWave3.h"

EnemyWaveManager::EnemyWaveManager(MainScene* scene)
	:scene_(scene)
{
	//TODO:完成時は戻す
	//wave_ = boost::shared_ptr<EnemyWave1>(new EnemyWave1(30, this));
	wave_ = boost::shared_ptr<EnemyWave3>(new EnemyWave3(this));
}

EnemyWaveManager::~EnemyWaveManager()
{
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

#include "stdafx.h"
#include "EnemyWaveManager.h"

#include "MainScene.h"
#include "EnemyWaveBase.h"
#include "EnemyWave1.h"

#include "EnemyWave3.h"

EnemyWaveManager::EnemyWaveManager(MainScene* scene)
	:scene_(scene)
{
	//TODO:�������͖߂�
	//wave_ = boost::shared_ptr<EnemyWave1>(new EnemyWave1(30, this));
	wave_ = boost::shared_ptr<EnemyWave3>(new EnemyWave3(this));
}

EnemyWaveManager::~EnemyWaveManager()
{
}

void EnemyWaveManager::SetWave(boost::shared_ptr<EnemyWaveBase> wave)
{
	//wave_���̂̍X�V�́C���̊֐����I�������ɍs��
	next_wave_ = wave;
	//�t���O�𗧂ĂĂ���
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

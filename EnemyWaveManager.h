#pragma once
#include "GameObjectHandle.h"
#include "Math.h"

class EnemyWaveBase;
class MainScene;

class EnemyWaveManager
{
public:
	EnemyWaveManager(MainScene* scene);
	~EnemyWaveManager();
	void SetWave(boost::shared_ptr<EnemyWaveBase> wave);
	GameObjectHandle SolveNearestEnemy();
	/// <summary>
	/// Scene���疈tick�Ăяo��
	/// </summary>
	void Update();
	MainScene* const scene_;
private:
	//�����Ă���Wave
	boost::shared_ptr<EnemyWaveBase> wave_;
	//���ɗ���Wave(SetWave�Ŏg��)
	boost::shared_ptr<EnemyWaveBase> next_wave_;
	//SetWave�Ŏg��
	bool has_switched_;
};
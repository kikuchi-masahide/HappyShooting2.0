#pragma once
#include "../Engine/GameObject.h"
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
	//���@�̃I�u�W�F�N�g�n���h����Ԃ�
	GameObjectHandle GetMyselfHandle();
	MainScene* const scene_;
	//���݂�Wave�ɂ��̓G�@��ǉ�����
	void AddEnemyInWave(GameObjectHandle enemy);
private:
	//�����Ă���Wave
	boost::shared_ptr<EnemyWaveBase> wave_;
	//���ɗ���Wave(SetWave�Ŏg��)
	boost::shared_ptr<EnemyWaveBase> next_wave_;
	//SetWave�Ŏg��
	bool has_switched_;
};
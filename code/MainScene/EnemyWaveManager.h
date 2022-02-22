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
	//Wave�̐؂�ւ����s�� Wave�̏o�������Ŏg��
	void SetWave(boost::shared_ptr<EnemyWaveBase> wave);
	GameObjectHandle SolveNearestEnemy();
	/// <summary>
	/// Scene���疈tick�Ăяo�� ������Wave���Z�b�g����Ă��Ȃ��Ȃ�Ή������Ȃ�
	/// </summary>
	void Update();
	//���@�̃I�u�W�F�N�g�n���h����Ԃ�
	//TODO:�Ȃ�ł��������ςȓn��������K�v�������� MainScene�ł̏����������ǂ��ɂ�������
	GameObjectHandle GetMyselfHandle();
	MainScene* const scene_;
	//���݂�Wave�ɂ��̓G�@��ǉ�����
	void AddEnemyInWave(GameObjectHandle enemy);
private:
	//�����Ă���Wave
	boost::shared_ptr<EnemyWaveBase> wave_;
	//���YWave�Ɋ܂܂��G�@
	std::list<GameObjectHandle> enemies_;
	//�S�ł��܂��Ȃ��-1�C�S�ł��m�F����tick����1��������
	unsigned int counter_;
};
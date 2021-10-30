#pragma once
#include "../Engine/GameObject.h"

class MainScene;
class EnemyWaveManager;

class EnemyWaveBase
{
public:
	EnemyWaveBase(unsigned int tick_after_clear, EnemyWaveManager* manager);
	virtual ~EnemyWaveBase();
	/// <summary>
	/// EnemyWaveManager�o�R�Ŗ�tick�Ăяo�����
	/// </summary>
	void Update();
	/// <summary>
	/// Wave���̓G����C���@�ɍł��߂����̂��v�Z����(�G�@�����݂��Ȃ��Ȃ��nullptr)
	/// </summary>
	GameObjectHandle SolveNearestEnemy();
protected:
	/// <summary>
	/// counter_ == tick_after_clear_��tick�ŌĂяo�����
	/// </summary>
	virtual void OnDelete() = 0;
	/// <summary>
	/// �Ď��Ώۂɂ��̃I�u�W�F�N�g��ǉ�
	/// </summary>
	void AddEnemy(GameObjectHandle object);
	EnemyWaveManager* const manager_;
private:
	std::vector<GameObjectHandle> enemies_;
	//����Wave���S�ł��ĉ�tick��Ƀf�X�g���N�^���Ăяo����(0�Ȃ�ΑS�ł���tick�ŌĂяo��)
	unsigned int tick_after_clear_;
	//�S�ł��܂��Ȃ��-1�C�S�ł��m�F����tick����1��������
	unsigned int counter_;
	//manager_����H��邯�ǂǂ�����tick��邱�ƂɂȂ�̂Ŏ����Ă���
	GameObjectHandle myself_handle_;
};


#pragma once
#include "../Engine/GameObject.h"

class MainScene;
class EnemyWaveManager;

/// <summary>
/// �G1Wave�̏������A����яo���������܂Ƃ߂�����
/// </summary>
class EnemyWaveBase
{
public:
	/// <summary>
	/// Wave�̏��������s��
	/// </summary>
	/// <param name="tick_after_clear">����Wave���S�Ō�A��tick���OnDelete()�����s���邩</param>
	EnemyWaveBase(unsigned int tick_after_clear, MainScene* main_scene);
	virtual ~EnemyWaveBase();
	//����Wave���S�ł��ĉ�tick��Ƀf�X�g���N�^���Ăяo����(0�Ȃ�ΑS�ł���tick�ŌĂяo��)
	const unsigned int tick_after_clear_;
	/// <summary>
	/// counter_ == tick_after_clear_��tick�ŌĂяo�����
	/// </summary>
	virtual void OnDelete() = 0;
protected:
	MainScene* main_scene_;
private:
};


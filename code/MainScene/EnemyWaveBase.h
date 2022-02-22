#pragma once
#include "../Engine/GameObject.h"

class MainScene;
class EnemyWaveManager;

/// <summary>
/// 敵1Waveの初期化、および出口処理をまとめたもの
/// </summary>
class EnemyWaveBase
{
public:
	/// <summary>
	/// Waveの初期化を行う
	/// </summary>
	/// <param name="tick_after_clear">このWaveが全滅後、何tick後にOnDelete()を実行するか</param>
	EnemyWaveBase(unsigned int tick_after_clear, MainScene* main_scene);
	virtual ~EnemyWaveBase();
	//このWaveが全滅して何tick後にデストラクタを呼び出すか(0ならば全滅したtickで呼び出す)
	const unsigned int tick_after_clear_;
	/// <summary>
	/// counter_ == tick_after_clear_のtickで呼び出される
	/// </summary>
	virtual void OnDelete() = 0;
protected:
	MainScene* main_scene_;
private:
};


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
	/// Sceneから毎tick呼び出す
	/// </summary>
	void Update();
	//自機のオブジェクトハンドルを返す
	GameObjectHandle GetMyselfHandle();
	MainScene* const scene_;
	//現在のWaveにこの敵機を追加する
	void AddEnemyInWave(GameObjectHandle enemy);
private:
	//今見ているWave
	boost::shared_ptr<EnemyWaveBase> wave_;
	//次に来るWave(SetWaveで使う)
	boost::shared_ptr<EnemyWaveBase> next_wave_;
	//SetWaveで使う
	bool has_switched_;
};
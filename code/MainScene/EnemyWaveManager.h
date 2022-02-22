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
	//Waveの切り替えを行う Waveの出口処理で使う
	void SetWave(boost::shared_ptr<EnemyWaveBase> wave);
	GameObjectHandle SolveNearestEnemy();
	/// <summary>
	/// Sceneから毎tick呼び出す ただしWaveがセットされていないならば何もしない
	/// </summary>
	void Update();
	//自機のオブジェクトハンドルを返す
	//TODO:なんでこういう変な渡し方する必要があるんや MainSceneでの初期化順をどうにかしたい
	GameObjectHandle GetMyselfHandle();
	MainScene* const scene_;
	//現在のWaveにこの敵機を追加する
	void AddEnemyInWave(GameObjectHandle enemy);
private:
	//今見ているWave
	boost::shared_ptr<EnemyWaveBase> wave_;
	//当該Waveに含まれる敵機
	std::list<GameObjectHandle> enemies_;
	//全滅がまだならば-1，全滅を確認したtickから1ずつ増える
	unsigned int counter_;
};
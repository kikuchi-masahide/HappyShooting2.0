#pragma once
#include "../Engine/GameObject.h"

class MainScene;
class EnemyWaveManager;

class EnemyWaveBase
{
public:
	EnemyWaveBase(unsigned int tick_after_clear, MainScene* main_scene);
	virtual ~EnemyWaveBase();
	/// <summary>
	/// EnemyWaveManager経由で毎tick呼び出される
	/// </summary>
	void Update();
	/// <summary>
	/// Wave中の敵から，自機に最も近いものを計算する(敵機が存在しないならばnullptr)
	/// </summary>
	GameObjectHandle SolveNearestEnemy();
	/// <summary>
	/// 監視対象にこのオブジェクトを追加
	/// </summary>
	// TODO:Wave6は自己複製が入るため、敵機の側から敵機を追加する必要があるため、
	// protected -> publicに変更したけど、これだけの理由でそうするのっていいんですか?
	void AddEnemy(GameObjectHandle object);
protected:
	/// <summary>
	/// counter_ == tick_after_clear_のtickで呼び出される
	/// </summary>
	virtual void OnDelete() = 0;
	MainScene* main_scene_;
private:
	std::vector<GameObjectHandle> enemies_;
	//このWaveが全滅して何tick後にデストラクタを呼び出すか(0ならば全滅したtickで呼び出す)
	unsigned int tick_after_clear_;
	//全滅がまだならば-1，全滅を確認したtickから1ずつ増える
	unsigned int counter_;
	//manager_から辿れるけどどうせ毎tickやることになるので持っておく
	GameObjectHandle myself_handle_;
};


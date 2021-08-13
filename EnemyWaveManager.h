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
	/// Scene‚©‚ç–ˆtickŒÄ‚Ño‚·
	/// </summary>
	void Update();
	MainScene* const scene_;
private:
	//¡Œ©‚Ä‚¢‚éWave
	boost::shared_ptr<EnemyWaveBase> wave_;
	//Ÿ‚É—ˆ‚éWave(SetWave‚Åg‚¤)
	boost::shared_ptr<EnemyWaveBase> next_wave_;
	//SetWave‚Åg‚¤
	bool has_switched_;
};
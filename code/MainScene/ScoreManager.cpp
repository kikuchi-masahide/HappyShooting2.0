#include "ScoreManager.h"

ScoreManager::ScoreManager()
	:score_(0),life_(life_initial_)
{
}

ScoreManager::~ScoreManager()
{
}

void ScoreManager::AddScore(int add)
{
	score_ += add;
}

void ScoreManager::ConsumeLife()
{
	life_--;
}

void ScoreManager::AddLife(int n)
{
	life_ += n;
}

bool ScoreManager::IsLifeRemaining()
{
	return (life_ >= 1);
}

int ScoreManager::GetScore() const
{
	return score_;
}

int ScoreManager::GetRemainingLife()
{
	return life_;
}

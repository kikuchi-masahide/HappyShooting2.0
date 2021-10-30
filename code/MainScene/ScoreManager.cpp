#include "ScoreManager.h"

ScoreManager::ScoreManager()
	:score_(0)
{
}

ScoreManager::~ScoreManager()
{
}

void ScoreManager::AddScore(int add)
{
	score_ += add;
}

int ScoreManager::GetScore() const
{
	return score_;
}

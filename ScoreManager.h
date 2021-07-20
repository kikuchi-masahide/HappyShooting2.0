#pragma once

//スコアを管理するクラス
class ScoreManager
{
public:
	ScoreManager();
	~ScoreManager();
	void AddScore(int add);
	int GetScore() const;
private:
	int score_;
};


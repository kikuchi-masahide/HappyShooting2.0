#pragma once

//スコアと自機の残機を管理するクラス
class ScoreManager
{
public:
	ScoreManager();
	~ScoreManager();
	void AddScore(int add);
	//自機の残機を1つ減らす
	void ConsumeLife();
	//時期の残機を増やす(MainSceneを経由して呼び出す 直接呼び出さない)
	void AddLife(int n);
	//自機残機が1つ以上残っているか否か
	bool IsLifeRemaining();
	int GetScore() const;
	int GetRemainingLife();
private:
	int score_;
	//最初の残機数
	static constexpr int life_initial_ = 3;
	int life_;
};


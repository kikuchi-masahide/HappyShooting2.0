#pragma once

//�X�R�A���Ǘ�����N���X
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


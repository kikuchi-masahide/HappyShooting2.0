#pragma once

//�X�R�A�Ǝ��@�̎c�@���Ǘ�����N���X
class ScoreManager
{
public:
	ScoreManager();
	~ScoreManager();
	void AddScore(int add);
	//���@�̎c�@��1���炷
	void ConsumeLife();
	//�����̎c�@�𑝂₷(MainScene���o�R���ČĂяo�� ���ڌĂяo���Ȃ�)
	void AddLife(int n);
	//���@�c�@��1�ȏ�c���Ă��邩�ۂ�
	bool IsLifeRemaining();
	int GetScore() const;
	int GetRemainingLife();
private:
	int score_;
	//�ŏ��̎c�@��
	static constexpr int life_initial_ = 3;
	int life_;
};


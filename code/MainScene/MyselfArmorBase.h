#pragma once

/// <summary>
/// ���@�̕��푕���̍X�V�A����ѕ`��@�\�E���������Ϗ��������N���X
/// </summary>
class MyselfArmorBase
{
public:
	MyselfArmorBase() {};
	virtual ~MyselfArmorBase() {};
	/// <summary>
	/// ���f�B�G�[�^���X�V����������Ƃ��Ăяo�����
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// �`�惿��ς���
	/// </summary>
	virtual void UpdateAlpha(double alpha) = 0;
	/// <summary>
	/// �e���o�����o���Ȃ�����ς���
	/// </summary>
	virtual void SetBulletAvailability(bool act) = 0;
private:
};


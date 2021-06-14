#pragma once

class Game;

/// <summary>
/// �e�L�[�E�}�E�X�{�^���̏�Ԃ�\��enum
/// None:off->off
/// Pressed:off->on
/// Released:on->off
/// Held:on->on
/// </summary>
enum class ButtonState :unsigned char {
	None,
	Pressed,
	Released,
	Held
};

/// <summary>
/// Game�����C���͂��Ǘ�����N���X
/// </summary>
class InputSystem :public boost::noncopyable{
public:
	/// <summary>
	/// Game����̂݌Ă΂ꂤ��R���X�g���N�^
	/// </summary>
	InputSystem(Game* _game);
	/// <summary>
	/// �V�[���C�I�u�W�F�N�g����Update���Ăяo�����O�̑O����(Game�݂̂��Ăяo����)
	void ProcessBeforeUpdate(Game* _game);
	/// <summary>
	/// �w��L�[�̏�Ԃ�ButtonState�^�ŕԂ�
	/// </summary>
	/// <param name="_key">�����L�[�̏ꍇ�Ή������啶���̃L�[�R�[�h('A'�Ȃ�)�C����ȊO�̏ꍇVK_�`�`�̊Y������ϐ�</param>
	/// <returns></returns>
	ButtonState GetKeyState(unsigned char _key);
	/// <summary>
	/// �O�t���[�����猻�t���[���ł̃}�E�X�̈ړ����x�N�g���Ŏ擾(���ʒu-�O�ʒu�C�������_)
	/// </summary>
	MatVec::Vector2 GetMouseMove();
	/// <summary>
	/// �}�E�X�̃X�N���[�����W���擾(���㌴�_�͂��̂܂�)
	/// </summary>
	MatVec::Vector2 GetMouseScreenPos();
private:
	Game* const mGame;
	//�O�E���t���[���̃L�[�{�[�h�̏�
	BYTE mKeyState[2][256];
	//mKeyState�CmMousePos�ł̌��t���[���󋵂̓Y����
	unsigned int mCurIndex;
	//�O�E���t���[���̃}�E�X�J�[�\���ʒu(����������̓X�N���[�����W�ł��邱�Ƃɒ���)
	MatVec::Vector2 mMousePos[2];
};
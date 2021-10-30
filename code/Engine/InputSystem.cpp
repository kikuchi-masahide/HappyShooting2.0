#include "InputSystem.h"

InputSystem::InputSystem(Game* _game)
	:mGame(_game)
{
	BOOST_ASSERT_MSG(mGame != nullptr, "InputSystem::InputSystem() should be called only in Game::Game()");
	mCurIndex = 0;
	GetKeyboardState(mKeyState[mCurIndex]);
	POINT point;
	GetCursorPos(&point);
	mMousePos[mCurIndex] = MatVec::Vector2(point.x, point.y);
}

void InputSystem::ProcessBeforeUpdate(Game* _game)
{
	BOOST_ASSERT_MSG(mGame == _game, "only Game::ProcessInput() can call InputSystem::ProcessBeforeUpdate()");
	//mCurIndex�̔��]
	mCurIndex = 1 - mCurIndex;
	//���݂̏�Ԃ�mKeyState[mCurIndex]�ɕۑ�
	GetKeyboardState(mKeyState[mCurIndex]);
	//�J�[�\���ʒu�̎擾
	POINT point;
	GetCursorPos(&point);
	mMousePos[mCurIndex] = MatVec::Vector2(point.x, point.y);
}

ButtonState InputSystem::GetKeyState(unsigned char _key)
{
	//�O�t���[���œ��͂�����Ă���
	if (mKeyState[1 - mCurIndex][_key] & 0x80)
	{
		if (mKeyState[mCurIndex][_key] & 0x80)
		{
			return ButtonState::Held;
		}
		else
		{
			return ButtonState::Released;
		}
	}
	else
	{
		if (mKeyState[mCurIndex][_key] & 0x80)
		{
			return ButtonState::Pressed;
		}
		else
		{
			return ButtonState::None;
		}
	}
}

MatVec::Vector2 InputSystem::GetMouseMove()
{
	MatVec::Vector2 vec = mMousePos[mCurIndex] - mMousePos[1 - mCurIndex];
	//�X�N���[�����Wy���W�͉������Ȃ̂Ŕ��]
	vec(1) *= -1;
	return vec;
}

MatVec::Vector2 InputSystem::GetMouseScreenPos()
{
	return mMousePos[mCurIndex];
}
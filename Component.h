#pragma once

class Scene;
class Game;

#include "ComponentHandle.h"
#include "GameObjectHandle.h"

/// <summary>
/// �I�u�W�F�N�g�̋@�\��\���N���X
/// �I�u�W�F�N�g�̍X�V������R���|�[�l���g�Əo�͂�����R���|�[�l���g�͗������̊��N���X����h��������
/// </summary>
// HACK:�R���|�[�l���g�����̃N���X�̔h���ɂ����C�����̒��g�E���f�[�^���^�N���X�ɂ���̂͂��肩?
class Component {
public:
	/// <param name="_order">�D��x �����قǐ�ɌĂяo�����</param>
	Component(GameObjectHandle _handle, int _order = 0);
	/// <summary>
	/// �R���|�|�l���g�̍X�V����
	/// </summary>
	virtual void Update() = 0;
	bool GetDeleteFlag() const { return mDeleteFlag; };
	void SetDeleteFlag() { mDeleteFlag = true; };
	const int mUpdPriority;
	const GameObjectHandle mObj;
protected:
	virtual ~Component();
	bool mDeleteFlag;
	//���g���w���n���h����Ԃ��֐�
	template<class T>
	ComponentHandle<T> This()
	{
		return ComponentHandle<T>((T*)this, &mHandles);
	}
private:
	bool mDeleteCheck;
	friend class GameObject;
	//�������w���n���h���̏W���̃|�C���^(void*���g���͉̂��Ƃ�������߂���)
	std::unordered_set<void*> mHandles;
	//&�ŃC���X�^���X�̃|�C���^���擾�����Ȃ�
	Component* operator&() const noexcept;
};
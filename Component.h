#pragma once

class GameObject;
class Scene;
class Game;
template<class T>
class ComponentHandle;

/// <summary>
/// �I�u�W�F�N�g�̋@�\��\���N���X
/// �I�u�W�F�N�g�̍X�V������R���|�[�l���g�Əo�͂�����R���|�[�l���g�͗������̊��N���X����h��������
/// </summary>
class Component {
public:
	/// <param name="_order">�D��x �����قǐ�ɌĂяo�����</param>
	Component(GameObject* _owner, boost::shared_ptr<std::set<void*>> _hset, int _order = 0);
	/// <summary>
	/// �R���|�|�l���g�̍X�V����
	/// </summary>
	virtual void Update() = 0;
	bool GetDeleteFlag() const { return mDeleteFlag; };
	void SetDeleteFlag() { mDeleteFlag = true; };
	virtual ~Component();
	Scene& GetScene() const;
	Game& GetGame() const;
	GameObject& mOwner;
	const int mUpdPriority;
protected:
	template<class T>
	ComponentHandle<T> This()
	{
		return ComponentHandle<T>((T*)this, mHandles);
	}
	bool mDeleteFlag;
private:
	//�������w���n���h���̏W���̃|�C���^(void*���g���͉̂��Ƃ�������߂���)
	boost::shared_ptr<std::set<void*>> mHandles;
	//&�ŃC���X�^���X�̃|�C���^���擾�����Ȃ�
	Component* operator&() const noexcept;
};
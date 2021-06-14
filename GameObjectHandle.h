#pragma once

class GameObject;

/// <summary>
/// GameObject���������Ɏg���n���h�� Scene::AddChild�̕Ԃ�l
/// �|�C���^�̂悤��->���Z�q�Ń����o�ɃA�N�Z�X�\
/// </summary>
class GameObjectHandle {
public:
	GameObjectHandle(const GameObjectHandle& _handle);
	/// <summary>
	/// Scene��AddChild���ł̂݌Ăяo�����R���X�g���N�^
	/// </summary>
	GameObjectHandle(GameObject* _obj, boost::shared_ptr<std::set<GameObjectHandle*>> _set);
	GameObjectHandle();
	~GameObjectHandle();
	//���̃n���h�����w��GameObject�݂̂�Reset���Ăяo����(_obj��mObject�ƈ�v���Ȃ����assert)
	void Reset(GameObject* _obj);
	GameObject* operator->() const noexcept;
	bool IsValid() const;
	GameObjectHandle& operator=(const GameObjectHandle& handle);
private:
	//���̃n���h�����w���I�u�W�F�N�g
	GameObject* mObject;
	//mObject���w���n���h����std::set�̃|�C���^
	boost::shared_ptr<std::set<GameObjectHandle*>> mHandleSet;
};
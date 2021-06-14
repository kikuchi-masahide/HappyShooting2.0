#pragma once

#include "Scene.h"
class Component;
class Game;
class GameObjectHandle;
template<class T>
class ComponentHandle;

/// <summary>
/// �V�[���Ɋ܂܂��I�u�W�F�N�g��\���N���X
/// </summary>
class GameObject final {
public:
	/// <summary>
	/// Scene::AddChild����Ăяo�����R���X�g���N�^
	/// </summary>
	GameObject(Scene* _scene, boost::shared_ptr<std::set<GameObjectHandle*>> _hset, MatVec::Vector2 _pos, double _scale, double _angle);
	MatVec::Vector2 GetPosition() const;
	MatVec::Vector2 SetPosition(MatVec::Vector2 _pos);
	double GetScale() const;
	double SetScale(double _sc);
	double GetRotation() const;
	double SetRotation(double _ro);
	bool GetDeleteFlag() const { return mDeleteFlag; };
	void SetDeleteFlag() { mDeleteFlag = true; };
	~GameObject();
	/// <summary>
	/// ���̃I�u�W�F�N�g��T�^��UpdateComponent��ǉ�(_args�̓R���X�g���N�^�ɓn���C_hset�ȍ~�̈���)
	/// concept����T�̐���������X(�ÓI��)�]��������
	/// </summary>
	template<class T,class... Args>
	ComponentHandle<T> AddUpdateComponent(Args... _args) {
		//���̃R���|�[�l���g���w���n���h���̏W��
		boost::shared_ptr<std::set<void*>> comphsetp(new std::set<void*>());
		//�R���|�[�l���g���g
		T* comppn = new T(this, comphsetp, _args...);
		boost::shared_ptr<Component> compp(comppn);
		mUpdateComponents.push_back(compp);
		//�Ԃ��n���h��
		ComponentHandle<T> comph(comppn, comphsetp);
		//�V�[���ɒǉ�
		mScene->AddUpdateComponent(this, comph);
		return comph;
	}
	template<class T, class... Args>
	ComponentHandle<T> AddOutputComponent(Args... _args) {
		//���̃R���|�[�l���g���w���n���h���̏W��
		boost::shared_ptr<std::set<void*>> comphsetp(new std::set<void*>());
		//�R���|�[�l���g���g
		T* comppn = new T(this, comphsetp, _args...);
		boost::shared_ptr<Component> compp(comppn);
		mOutputComponents.push_back(compp);
		//�Ԃ��n���h��
		ComponentHandle<T> comph(comppn, comphsetp);
		//�V�[���ɒǉ�
		mScene->AddOutputComponent(this, comph);
		return comph;
	};
	//�t���O�������Ă���R���|�[�l���g���폜
	void DeleteFlagedComponents(Scene* _scene);
	Scene& GetScene() const { return *mScene; };
	Game& GetGame() const;
private:
	Scene* mScene;
	/// <summary>
	/// �I�u�W�F�N�g�̒��S���W
	/// </summary>
	MatVec::Vector2 mPosition;
	double mScale;
	/// <summary>
	/// ��]�p�x(���v���A�x��)
	/// </summary>
	double mRotation;
	//���̃I�u�W�F�N�g�̎��X�V�E�o�̓R���|�[�l���g
	std::list<boost::shared_ptr<Component>> mUpdateComponents;
	std::list<boost::shared_ptr<Component>> mOutputComponents;
	//���̃I�u�W�F�N�g���w���n���h����set
	boost::shared_ptr<std::set<GameObjectHandle*>> mHandles;
	bool mDeleteFlag;
	GameObject* operator&() const noexcept;
};
#pragma once

#include "Component.h"
#include "GameObjectHandle.h"
#include "Math.h"

class Scene;
class Game;
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
	GameObject(Scene* _scene, MatVec::Vector2 _pos, double _scale, double _angle);
	MatVec::Vector2 GetPosition() const;
	MatVec::Vector2 SetPosition(const MatVec::Vector2& _pos);
	double GetScale() const;
	double SetScale(double _sc);
	double GetRotation() const;
	double SetRotation(double _ro);
	bool GetDeleteFlag() const { return mDeleteFlag; };
	void SetDeleteFlag() { mDeleteFlag = true; };
	/// <summary>
	/// ���̃I�u�W�F�N�g��T�^��UpdateComponent��ǉ�(_args�̓R���X�g���N�^�ɓn�������ŁC������mObj������������)
	/// concept����T�̐���������X(�ÓI��)�]��������
	/// </summary>
	template<class T, class... Args>
	ComponentHandle<T> AddUpdateComponent(Args... _args) {
		//�R���|�[�l���g���g
		T* comp = new T(This(), _args...);
		mUpdateComponents.push_back(comp);
		ComponentHandle<T> handle = comp->This<T>();
		//�V�[���ɒǉ�
		AddUpdateComponentToScene(static_cast<ComponentHandle<Component>>(handle));
		return handle;
	}
	/// <summary>
	/// ���̃I�u�W�F�N�g��T�^��OutputComponent��ǉ�(_args�̓R���X�g���N�^�ɓn�������ŁC������mObj������������)
	/// concept����T�̐���������X(�ÓI��)�]��������
	/// </summary>
	template<class T, class... Args>
	ComponentHandle<T> AddOutputComponent(Args... _args) {
		//�R���|�[�l���g���g
		T* comp = new T(This(), _args...);
		mOutputComponents.push_back(comp);
		ComponentHandle<T> handle = comp->This<T>();
		//�V�[���ɒǉ�
		AddOutputComponentToScene(static_cast<ComponentHandle<Component>>(handle));
		return handle;
	};
	Game& GetGame();
private:
	friend class Scene;
	Scene* mScene;
	~GameObject();
	//�t���O�������Ă���R���|�[�l���g���폜
	void DeleteFlagedComponents();
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
	std::list<Component*> mUpdateComponents;
	std::list<Component*> mOutputComponents;
	//���̃I�u�W�F�N�g���w���n���h����set
	std::set<GameObjectHandle*> mHandles;
	bool mDeleteFlag;
	GameObject* operator&() const noexcept;
	//AddUpdateComponent���ŌĂ΂��
	//#include�̕�������v�����邽�ߕʊ֐��ɕ���
	void AddUpdateComponentToScene(ComponentHandle<Component> _handle);
	void AddOutputComponentToScene(ComponentHandle<Component> _handle);
	/// <summary>
	/// Scene::AddObject�ŌĂяo�����C���g���w���n���h����Ԃ��֐�
	/// </summary>
	GameObjectHandle This();
	//���̃R���|�[�l���g��delete���f�X�g���N�^���Ă�
	//(���Ƃ��Ƃ��̃|�C���^�������Ă���list�����erase�͂��Ȃ�)
	void DeleteComponent(Component* _component);
};
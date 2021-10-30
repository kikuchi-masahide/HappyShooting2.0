#pragma once

#include "GameObject.h"
#include "Layer.h"
#include "InputSystem.h"
#include "Math/Math.h"

class Game;
class UIScreen;
class InputSystem;

/// <summary>
/// �V�[����\���N���X
/// </summary>
class Scene {
public:
	//�R���X�g���N�^���Ăяo����̂�_game���g��AddChild�̂�
	Scene(Game* _game);
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update(InputSystem* _input);
	/// <summary>
	/// GameObject��UIScreen��X�V�����̑O�Ɏ��s�����Coverride�\�ȓƎ�����
	/// </summary>
	virtual void PriorUniqueUpdate();
	/// <summary>
	/// GameObject��UIScreen��X�V�����̌�Ɏ��s�����Coverride�\�ȓƎ�����
	/// </summary>
	virtual void PosteriorUniqueUpdate();
	/// <summary>
	/// �o�͊֐� �����ڍ�:
	/// OutputComponents��Update()���s
	/// Layer�̕ύX���f��Draw()���s
	/// UniqueOutput()
	/// DeleteFlag�̗���GameObject�CComponent�CLayer�̍폜�ƕۗ����Ă������̂̒ǉ�
	/// </summary>
	void Output();
	/// <summary>
	/// GameObject����Update�̑O�Ɏ��s�����Coverride�\�ȓƎ�����
	/// </summary>
	virtual void PriorUniqueOutput();
	/// <summary>
	/// GameObject����Update�̌�Ɏ��s�����Coverride�\�ȓƎ�����
	/// (���̃t���[���ł�GameObject�CComponent�ǉ��͂܂��ۗ����)
	/// </summary>
	virtual void PosteriorUniqueOutput();
	GameObjectHandle AddObject(MatVec::Vector2 _pos, double _scale, double _angle);
	Game &mGame;
	bool GetDeleteFlag() const { return mDeleteFlag; };
	void SetDeleteFlag() { mDeleteFlag = true; };
	//���̃V�[���ɍX�V�E�o�̓R���|�[�l���g��ǉ�����
	//GameObject::AddUpdate�EOutputComponent����Ăяo�����
	void AddUpdateComponent(GameObject* _obj, ComponentHandle<Component> _handle);
	//���̃V�[���ɍX�V�E�o�̓R���|�[�l���g��ǉ�����
	//GameObject::AddUpdate�EOutputComponent����Ăяo�����
	void AddOutputComponent(GameObject* _obj, ComponentHandle<Component> _handle);
	template<class T, class... Args>
	LayerHandle<T> AddLayer(Args... _args)
	{
		if (is_executing_destructor_)
		{
			return LayerHandle<T>();
		}
		T* layerp= new T(_args...);
		//���ڒǉ����Ă悢�Ȃ�΂�������
		if (mIsObjCompAddable)mLayers.insert(layerp);
		else mPandingLayers.insert(layerp);
		return layerp->This<T>();
	}
	/// <summary>
	/// T�^UI��ʂ̒ǉ�
	/// </summary>
	/// <param name="..._args">�R���X�g���N�^�ɓn������</param>
	template<class T,class... Args>
	T* AddUIScreen(Args... _args)
	{
		if (is_executing_destructor_)
		{
			return nullptr;
		}
		if (mIsObjCompAddable)
		{
			if (mUIScreens.size() == 0)
			{
				mPrevMousePosForUIScreens.push_back(mPrevMousePosForComps);
			}
			else
			{
				mPrevMousePosForUIScreens.push_back(mPrevMousePosForUIScreens.back());
			}
			auto ptr = new T(this, _args...);
			mUIScreens.push_back(ptr);
			mUpdateFlagForUIScreens.push_back(true);
			mInputFlagForUIScreens.push_back(true);
			return ptr;
		}
		else
		{
			auto ptr = new T(this, _args...);
			mPandingUIScreens.push_back(ptr);
			return ptr;
		}
	}
	/// <summary>
	///�e�L�[�E�}�E�X�̃{�^���̏�Ԃ��󂯎��
	/// </summary>
	ButtonState GetKeyState(unsigned char _key);
	/// <summary>
	//�}�E�X�̃N���C�A���g���W�𓾂�(�������_)
	/// </summary>
	MatVec::Vector2 GetMouseClientPos(unsigned int _windowid);
	/// <summary>
	//�}�E�X�̈ړ��x�N�g���𓾂�(�������_)
	/// </summary>
	MatVec::Vector2 GetMouseMove();
	/// <summary>
	//�}�E�X�̃X�N���[�����W�𓾂�(���㌴�_)
	/// </summary>
	MatVec::Vector2 GetMouseScreenPos();
protected:
	bool mDeleteFlag;
	virtual ~Scene();
private:
	friend Game;
	bool mDeleteCheck;
	class ComponentHandleCompare {
	public:
		bool operator()(const ComponentHandle<Component>& left, const ComponentHandle<Component>& right) const {
			if (!left.IsValid())return false;
			if (!right.IsValid())return true;
			return left->mUpdPriority < right->mUpdPriority;
		}
	};

	class LayerCompare {
	public:
		bool operator()(const Layer* left, const Layer* right) const {
			return left->GetZ() < right->GetZ();
		}
	};

	//���g�̎���GameObject�̃��X�g�y�ѕۗ����̃I�u�W�F�N�g
	std::list<GameObject*> mObjs;
	std::vector<GameObject*> mPandingObjs;
	//�R���|�[�l���g������set�̂��߂̏�����r�t�@���N�^
	//���g�̎��X�V�E�o�̓R���|�[�l���g�̃��X�g�C����ѕۗ��R���|�[�l���g
	std::multiset<ComponentHandle<Component>, ComponentHandleCompare> mUpdateComponents;
	std::vector<ComponentHandle<Component>> mPandingUpdateComponents;
	std::multiset<ComponentHandle<Component>, ComponentHandleCompare> mOutputComponents;
	std::vector<ComponentHandle<Component>> mPandingOutputComponents;
	//�����̎��S�X�V�E�o�̓R���|�[�l���g��Update���Ăяo��(�ۗ��R���|�[�l���g�̂���͎��s���Ȃ�)
	void LaunchUpdateComponents();
	void LaunchOutputComponents();
	//�R���|�[�l���g�E�I�u�W�F�N�g�𒼐ڃ��X�g�ɓ�����邩?
	bool mIsObjCompAddable;
	//Delete�t���O�������Ă���R���|�[�l���g�E�I�u�W�F�N�g���폜
	void DeleteObjComp();
	GameObject* operator&() const noexcept;
	//Z���W�����Ŏ��o��(�E��n!)
	std::set<Layer*, LayerCompare> mLayers;
	std::set<Layer*, LayerCompare> mPandingLayers;
	//�����̎���Layer��Output���s��
	void OutputLayer();
	//DeleteFlag�����Ă�Layer�̏���
	void DeleteLayers();
	//�����Ă���UIScreen�Q(�Y�����̑傫�����̂���ɒǉ����ꂽUIScreen)
	std::vector<UIScreen*> mUIScreens;
	//�ۗ�UIScreen
	std::vector<UIScreen*> mPandingUIScreens;
	InputSystem* mInputSystem;
	//��tick�CComponent�ɓ��͏���n�����ۂ�
	bool mInputFlagForComps;
	//��tick�C�Ή�UIScreen�ɓ��͏���n�����ۂ�
	std::vector<bool> mInputFlagForUIScreens;
	//��tick�CComponent��Update�����s���邩�ۂ�
	bool mUpdateFlagForComps;
	//��tick�C�Ή�UIScreen��Update�����s���邩�ۂ�
	std::vector<bool> mUpdateFlagForUIScreens;
	//GetButtonState���Ŏg���C���͏���n�����ۂ��̃t���O
	bool mInputFlag;
	//GetClientMousePos���Ŏg���C�Otick�ł̃}�E�X�ʒu
	MatVec::Vector2 mPrevMousePos;
	//Comps�ɂƂ��Ă̑Otick�}�E�X�ʒu(���㌴�_�X�N���[�����W)
	MatVec::Vector2 mPrevMousePosForComps;
	//UIScreen�ɂƂ��Ă̑Otick�}�E�X�ʒu(���㌴�_�X�N���[�����W)
	std::vector<MatVec::Vector2> mPrevMousePosForUIScreens;
	void DeleteUIScreen();
	//UIScreen��Update��������Ăяo��
	void LaunchUIScreenUpdate();
	//UIScreen��Output��������Ăяo��
	void LaunchOutputUIScreens();
	//���̃I�u�W�F�N�g�̃|�C���^��delete���f�X�g���N�^���Ă�
	void DeleteObject(GameObject* _object);
	//���̃��C���[�̃|�C���^��delete���f�X�g���N�^���Ă�
	void DeleteLayer(Layer* _layer);
	//�ۗ����̃I�u�W�F�N�g�����}�[�W
	void ProcessPandings();
	//�f�X�g���N�^���s���̂�true
	bool is_executing_destructor_;
};
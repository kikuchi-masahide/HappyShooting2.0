#include "Scene.h"
#include "GameObject.h"
#include "GameObjectHandle.h"
#include "Component.h"
#include "ComponentHandle.h"
#include "UIScreen.h"
#include "Game.h"
#include "window.h"

Scene::Scene(Game* _game)
	:mGame(*_game), mIsObjCompAddable(true), mInputSystem(nullptr), mPrevMousePos(MatVec::Vector2(0, 0)), mInputFlag(true), mInputFlagForComps(true), mUpdateFlagForComps(true), mDeleteCheck(false)
{
	BOOST_ASSERT(_game != nullptr);
}

void Scene::Update(InputSystem* _input)
{
	mInputSystem = _input;
	//�������炵�΂炭�̊ԁC�ǉ������I�u�W�F�N�g�E�R���|�[�l���g�͕ۗ��ɓ����
	mIsObjCompAddable = false;
	//�D��x�̍����C�Ǝ��X�V����
	PriorUniqueUpdate();
	//UIScreen�Ƀu���b�N����ĂȂ����Update�����s
	if (mUpdateFlagForComps)
	{
		mInputFlag = mInputFlagForComps;
		LaunchUpdateComponents();
	}
	LaunchUIScreenUpdate();
	PosteriorUniqueUpdate();
}

void Scene::PriorUniqueUpdate()
{
}

void Scene::PosteriorUniqueUpdate()
{
}

void Scene::Output()
{
	PriorUniqueOutput();
	LaunchOutputComponents();
	OutputLayer();
	LaunchOutputUIScreens();
	PosteriorUniqueOutput();
	mGame.mdx12.ProcessCommands();
	//�ۗ����Ă����I�u�W�F�N�g�E�R���|�[�l���g�̏������s��
	DeleteObjComp();
	DeleteLayers();
	DeleteUIScreen();
	mIsObjCompAddable = true;
	ProcessPandings();
}

void Scene::PriorUniqueOutput()
{
}

void Scene::PosteriorUniqueOutput()
{
}

GameObjectHandle Scene::AddObject(MatVec::Vector2 _pos, double _scale, double _angle)
{
	//�ǉ�����I�u�W�F�N�g
	GameObject* objp(new GameObject(this, _pos, _scale, _angle));
	//���ڒǉ����Ă悢�Ȃ�΂�������
	if (mIsObjCompAddable)mObjs.push_back(objp);
	else mPandingObjs.push_back(objp);
	return objp->This();
}

void Scene::AddUpdateComponent(GameObject* _obj, ComponentHandle<Component> _handle)
{
	BOOST_ASSERT(_obj != nullptr);
	if (mIsObjCompAddable)mUpdateComponents.insert(_handle);
	else mPandingUpdateComponents.push_back(_handle);
}

void Scene::AddOutputComponent(GameObject* _obj, ComponentHandle<Component> _handle)
{
	BOOST_ASSERT(_obj != nullptr);
	if (mIsObjCompAddable) {
		mOutputComponents.insert(_handle);
	}
	else
	{
		mPandingOutputComponents.push_back(_handle);
	}
}

Scene::~Scene() {
	BOOST_ASSERT_MSG(mDeleteCheck == true, "irregal destructor call without Game permission");
	//GameObject�̍폜����
	for (auto object : mObjs)
	{
		DeleteObject(object);
	}
	for (auto object : mPandingObjs)
	{
		DeleteObject(object);
	}
	//Layer�̍폜����
	for (auto layer : mLayers)
	{
		DeleteLayer(layer);
	}
	for (auto layer : mPandingLayers)
	{
		DeleteLayer(layer);
	}
	//UIScreen�̍폜����
	for (auto uiscreen : mUIScreens)
	{
		delete uiscreen;
	}
	for (auto uiscreen : mPandingUIScreens)
	{
		delete uiscreen;
	}
}

ButtonState Scene::GetKeyState(unsigned char _key)
{
	if (mInputFlag)
	{
		return mInputSystem->GetKeyState(_key);
	}
	else
	{
		return ButtonState::None;
	}
}

MatVec::Vector2 Scene::GetMouseClientPos(unsigned int _windowid)
{
	//���㌴�_
	MatVec::Vector2 screenpos = GetMouseScreenPos();
	//�X�N���[�����W
	POINT mousepos;
	mousepos.x = screenpos(0);
	mousepos.y = screenpos(1);
	auto window = mGame.GetWindow(_windowid);
	auto hwnd = window->GetWindowHandle();
	//�N���C�A���g���W�ɕϊ�
	ScreenToClient(hwnd, &mousepos);
	//�E�B���h�E�̍��������
	auto windowheight = window->GetWindowSize().bottom - window->GetWindowSize().top;
	//�������_�ɕϊ�
	mousepos.y = windowheight - mousepos.y;
	return MatVec::Vector2(mousepos.x, mousepos.y);
}

MatVec::Vector2 Scene::GetMouseMove()
{
	if (mInputFlag)
	{
		//�X�N���[�����W(���㌴�_)
		MatVec::Vector2 vec = mInputSystem->GetMouseScreenPos() - mPrevMousePos;
		//�������_�ɏC��
		vec(1) *= -1;
		return vec;
	}
	else
	{
		//���͂�Ԃ������Ȃ��ꍇ�ړ������ŕԂ�
		return MatVec::Vector2(0, 0);
	}
}

MatVec::Vector2 Scene::GetMouseScreenPos()
{
	if (mInputFlag)
	{
		return mInputSystem->GetMouseScreenPos();
	}
	else
	{
		return mPrevMousePos;
	}
}

void Scene::LaunchUpdateComponents()
{
	for (auto itr = mUpdateComponents.begin(); itr != mUpdateComponents.end(); itr++)
	{
		(*itr)->Update();
	}
}

void Scene::LaunchOutputComponents()
{
	for (auto itr = mOutputComponents.begin(); itr != mOutputComponents.end(); itr++)
	{
		(*itr)->Update();
	}
}

void Scene::DeleteObjComp()
{
	//�S�I�u�W�F�N�g�����
	auto objitr = mObjs.begin();
	while (objitr != mObjs.end()) {
		//���̃I�u�W�F�N�g�̃t���O�������Ă���Ȃ�Ώ���
		if ((*objitr)->GetDeleteFlag()) {
			DeleteObject(*objitr);
			objitr = mObjs.erase(objitr);
		}
		else {
			//�I�u�W�F�N�g�ɂ���Ȃ��R���|�[�l���g���폜������
			(*objitr)->DeleteFlagedComponents();
			objitr++;
		}
	}
	//�_���O�����O�n���h���폜
	auto itr = mUpdateComponents.begin();
	while (itr != mUpdateComponents.end()) {
		if (!(itr->IsValid()))itr = mUpdateComponents.erase(itr);
		else itr++;
	}
	itr = mOutputComponents.begin();
	while (itr != mOutputComponents.end()) {
		if (!(itr->IsValid()))itr = mOutputComponents.erase(itr);
		else itr++;
	}
}

void Scene::OutputLayer()
{
	//z�̕ύX��������Layer�����������C�����łȂ�����Rect���X�V
	std::set<Layer*, LayerCompare> zchanged;
	auto itr = mLayers.begin();
	while (itr != mLayers.end())
	{
		if ((*itr)->HasZChanged())
		{
			zchanged.insert(*itr);
			itr = mLayers.erase(itr);
		}
		else {
			(*itr)->FlushZRectChange(*itr);
			itr++;
		}
	}
	//z�ύX����Layer���t���b�V�����CmLayers�ɖ߂�
	itr = zchanged.begin();
	while (itr != zchanged.end())
	{
		(*itr)->FlushZRectChange(*itr);
		mLayers.insert(*itr);
		itr++;
	}
	//mLayers��Output���Ăяo��
	itr = mLayers.begin();
	while (itr != mLayers.end())
	{
		(*itr)->Draw();
		itr++;
	}
}

void Scene::DeleteLayers()
{
	//Delete�t���O���Ă�Layer���폜
	auto itr = mLayers.begin();
	while (itr != mLayers.end())
	{
		if ((*itr)->GetDeleteFlag())
		{
			DeleteLayer(*itr);
			mLayers.erase(*itr);
		}
		else {
			itr++;
		}
	}
}

void Scene::DeleteUIScreen()
{
	int n = mUIScreens.size() - 1;
	//�Y�������傫�������猩�ď����ׂ�UIScreen���폜
	for (; n >= 0; n--)
	{
		if (mUIScreens[n]->GetDeleteFlag() == false)break;
		delete mUIScreens[n];
		mUIScreens.erase(mUIScreens.begin() + n);
		mPrevMousePosForUIScreens.erase(mPrevMousePosForUIScreens.begin() + n);
		mInputFlagForUIScreens.erase(mInputFlagForUIScreens.begin() + n);
		mUpdateFlagForUIScreens.erase(mUpdateFlagForUIScreens.begin() + n);
	}
	//mMousePosFor~�̍X�V
	for (n = 0; n < mUIScreens.size(); n++)
	{
		if (mInputFlagForUIScreens[n])
		{
			mPrevMousePosForUIScreens[n] = GetMouseScreenPos();
		}
	}
	if (mInputFlagForComps)
	{
		mPrevMousePosForComps = GetMouseScreenPos();
	}
	//mInput/UpdateFlagFor~�̍X�V
	if (mUIScreens.size() == 0)
	{
		mInputFlagForComps = true;
		mUpdateFlagForComps = true;
	}
	else
	{
		mInputFlagForUIScreens.back() = true;
		for (n = mUIScreens.size() - 2; n >= 0; n--)
		{
			mInputFlagForUIScreens[n] = mInputFlagForUIScreens[n + 1];
			if (mInputFlagForUIScreens[n] &&
				(mUIScreens[n + 1]->DoesInputGoThrough() == false)
				)
			{
				mInputFlagForUIScreens[n] = false;
			}
		}
		mInputFlagForComps = mInputFlagForUIScreens[0];
		if (mInputFlagForComps &&
			(mUIScreens[0]->DoesInputGoThrough() == false))
		{
			mInputFlagForComps = false;
		}
		mUpdateFlagForUIScreens.back() = true;
		for (n = mUIScreens.size() - 2; n >= 0; n--)
		{
			mUpdateFlagForUIScreens[n] = mUpdateFlagForUIScreens[n + 1];
			if (mUpdateFlagForUIScreens[n] &&
				(mUIScreens[n + 1]->DoesUpdateComp() == false))
			{
				mUpdateFlagForUIScreens[n] = false;
			}
		}
		mUpdateFlagForComps = mUpdateFlagForUIScreens[0];
		if (mUpdateFlagForComps &&
			(mUIScreens[0]->DoesUpdateComp() == false))
		{
			mUpdateFlagForComps = false;
		}
	}
}

void Scene::LaunchUIScreenUpdate()
{
	if (mUIScreens.size() == 0)return;
	for (int n = 0; n < mUIScreens.size(); n++)
	{
		//����UIScreen��Update�����s����Ȃ�΁CInput�̎󂯎��ۂ�ݒ肵��Update���Ăяo��
		if (mUpdateFlagForUIScreens[n])
		{
			mInputFlag = mInputFlagForUIScreens[n];
			mPrevMousePos = mPrevMousePosForUIScreens[n];
			mUIScreens[n]->Update();
		}
	}
}

void Scene::LaunchOutputUIScreens()
{
	for (int n = 0; n < mUIScreens.size(); n++)
	{
		mUIScreens[n]->Output();
	}
}

void Scene::DeleteObject(GameObject* _object)
{
	delete _object;
}

void Scene::DeleteLayer(Layer* _layer)
{
	_layer->mDeleteCheck = true;
	delete _layer;
}

void Scene::ProcessPandings()
{
	//�ۗ����Ă����I�u�W�F�N�g�E�R���|�[�l���g��ǉ�
	for (auto& obj : mPandingObjs) {
		mObjs.push_back(obj);
	}
	mPandingObjs.clear();
	for (auto& handle : mPandingUpdateComponents) {
		mUpdateComponents.insert(handle);
	}
	mPandingUpdateComponents.clear();
	for (auto& handle : mPandingOutputComponents) {
		mOutputComponents.insert(handle);
	}
	mPandingOutputComponents.clear();

	//Panding��Layer���t���b�V����mLayer�ɒǉ�
	auto itr = mPandingLayers.begin();
	while (itr != mPandingLayers.end())
	{
		(*itr)->FlushZRectChange(*itr);
		mLayers.insert(*itr);
		itr++;
	}
	mPandingLayers.clear();

	//Panding�ɂ���UIScreen�̒ǉ�
	for (int n = 0; n < mPandingUIScreens.size(); n++)
	{
		mUIScreens.push_back(mPandingUIScreens[n]);
		mPrevMousePosForUIScreens.push_back(GetMouseScreenPos());
		mUpdateFlagForUIScreens.push_back(true);
		mInputFlagForUIScreens.push_back(true);
	}
	mPandingUIScreens.clear();
}

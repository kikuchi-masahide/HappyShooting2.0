#include "Scene.h"
#include "GameObject.h"
#include "Component.h"
#include "UIScreen.h"
#include "Game.h"
#include "window.h"

Scene::Scene(Game* _game)
	:mGame(*_game), mIsObjCompAddable(true), mInputSystem(nullptr), mPrevMousePos(MatVec::Vector2(0, 0)), mInputFlag(true), mInputFlagForComps(true), mUpdateFlagForComps(true), mDeleteCheck(false),is_executing_destructor_(false)
{
	BOOST_ASSERT(_game != nullptr);
}

void Scene::Update(InputSystem* _input)
{
	auto start = timeGetTime();
	auto end = start;
	auto& profiler = mGame.profiler_;
	mInputSystem = _input;
	//�������炵�΂炭�̊ԁC�ǉ������I�u�W�F�N�g�E�R���|�[�l���g�͕ۗ��ɓ����
	mIsObjCompAddable = false;

	//�D��x�̍����C�Ǝ��X�V����
	PriorUniqueUpdate();
	end = timeGetTime();
	profiler.SetPriorUniqueUpdateTime(end - start);
	start = end;

	//UIScreen�Ƀu���b�N����ĂȂ����Update�����s
	if (mUpdateFlagForComps)
	{
		mInputFlag = mInputFlagForComps;
		LaunchUpdateComponents();
		end = timeGetTime();
		profiler.SetLaunchUpdateComponentsTime(end - start);
		start = end;
	}

	LaunchUIScreenUpdate();
	end = timeGetTime();
	profiler.SetLaunchUIScreenUpdateTime(end - start);
	start = end;

	PosteriorUniqueUpdate();
	end = timeGetTime();
	profiler.SetPosteriorUniqueUpdateTime(end - start);
}

void Scene::PriorUniqueUpdate()
{
}

void Scene::PosteriorUniqueUpdate()
{
}

void Scene::Output()
{
	auto start = timeGetTime();
	auto end = start;
	auto& profiler = mGame.profiler_;

	PriorUniqueOutput();
	end = timeGetTime();
	profiler.SetPriorUniqueOutputTime(end - start);
	start = end;

	LaunchOutputComponents();
	end = timeGetTime();
	profiler.SetLaunchOutputComponentsTime(end - start);
	start = end;

	OutputLayer();
	end = timeGetTime();
	profiler.SetOutputLayerTime(end - start);
	start = end;

	LaunchOutputUIScreens();
	end = timeGetTime();
	profiler.SetLaunchOutputUIScreensTime(end - start);
	start = end;

	PosteriorUniqueOutput();
	end = timeGetTime();
	profiler.SetPosteriorUniqueOutputTime(end - start);
	start = end;

	mGame.mdx12.ProcessCommands();
	end = timeGetTime();
	profiler.SetProcessCommandsTime(end - start);
	start = end;

	//�ۗ����Ă����I�u�W�F�N�g�E�R���|�[�l���g�̏������s��
	DeleteObjComp();
	end = timeGetTime();
	profiler.SetDeleteObjCompTime(end - start);
	start = end;

	DeleteLayers();
	end = timeGetTime();
	profiler.SetDeleteLayersTime(end - start);
	start = end;

	DeleteUIScreen();
	end = timeGetTime();
	profiler.SetDeleteUIScreenTime(end - start);
	start = end;

	mIsObjCompAddable = true;
	ProcessPandings();
	end = timeGetTime();
	profiler.SetProcessPandingsTime(end - start);
}

void Scene::PriorUniqueOutput()
{
}

void Scene::PosteriorUniqueOutput()
{
}

GameObjectHandle Scene::AddObject(MatVec::Vector2 _pos, double _scale, double _angle)
{
	//�f�X�g���N�^���s���ɌĂяo���ꂽ�牽�����Ȃ�
	if (is_executing_destructor_)
	{
		return GameObjectHandle();
	}
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
	//HACK:���̊֐����ŃI�u�W�F�N�g�Ȃǂ̃f�X�g���N�^���Ăяo���Ă���Œ��ɁCAddObject�Ȃǂ��Ăяo�����ƁC
	//�ǂ����g��Ȃ��̂ɃC���X�^���X���������邱�ƂɂȂ�̂ɉ����C
	//�V�����C���X�^���X�̃f�X�g���N�^���炳��ɐV�����C���X�^���X���ł�����ƁC���Ȃ�ʓ|�Ȃ��Ƃ�
	//�Ȃ肻���Ȃ̂ŁCis_executing_destructor_����ł͐������~�߂�悤�Ɍ��󂵂Ă���D
	//���l�̂��Ƃ�Game�ł��s���Ă���D
	//�������̏ꍇ�CAddObject������Ԃ����n���h����valid���m���߂Ȃ��Ă͂����Ȃ��Ȃ�̂���_�D
	//�I�u�W�F�N�g�̃f�X�g���N�^�����s����O�̏I��������2��ނɕ�����Ή������邩������Ȃ����C
	//���󂻂̃`�F�b�N�@�\���݂����Ȃ����ߌ�����
	is_executing_destructor_ = true;
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
	for (auto itr = mUpdateComponents.begin(); itr != mUpdateComponents.end();)
	{
		//�Otick��component�폜�Ŗ����w���Ă���n���h�����폜
		if (!(itr->IsValid()))
		{
			itr = mUpdateComponents.erase(itr);
		}
		else {
			(*itr)->Update();
			itr++;
		}
	}
}

void Scene::LaunchOutputComponents()
{
	for (auto itr = mOutputComponents.begin(); itr != mOutputComponents.end();)
	{
		if (!(itr->IsValid()))
		{
			itr = mOutputComponents.erase(itr);
		}
		else {
			(*itr)->Update();
			itr++;
		}
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
#include "Game.h"
#include "window.h"
#include "Scene.h"

#pragma comment(lib,"winmm.lib")

/// <summary>
/// �Q�[���S�̂̏�����
/// </summary>
/// <returns>�������ۂ�</returns>
bool Game::Initialize()
{
	Log::Init();
	mdx12.Initialize();
	mIsSceneChangable = true;
	mCurrentSwapChain = -1;
	//�J�[�\���̕\��������
	//int cursor_counter;
	//do {
	//	cursor_counter = ShowCursor(FALSE);
	//} while (cursor_counter >= 0);
	return true;
}

/// <summary>
/// �Q�[���̏I������
/// </summary>
void Game::Shutdown()
{
	is_executing_destructor_ = true;
	//�V�[���̍폜
	DeleteScene(mCurrentScene);
	if (mPandingScene != nullptr)
	{
		DeleteScene(mPandingScene);
	}

	//DX12�܂��̃N���[���A�b�v
	mdx12.CleanUp();
}

Game::Game()
	:mTexManager(this),mShaderManager(this),mInputSystem(this),is_executing_destructor_(false)
{
}

boost::shared_ptr<Window> Game::GetWindow(unsigned int _windownum)
{
	//���݃`�F�b�N
	auto itr = mWindows.find(_windownum);
	BOOST_ASSERT_MSG(itr != mWindows.end(), "unregistered windowID");
	return itr->second;
}

void Game::AddWindow(WNDPROC _wndproc, LPCWSTR _classID, int _width, int _height, LPCWSTR _windowTitle,unsigned int _windowid)
{
	//�E�B���h�EID�̏d���`�F�b�N
	BOOST_ASSERT_MSG(mWindows.find(_windowid) == mWindows.end(), "windowID duplicating");
	//�E�B���h�E�̒ǉ�
	boost::shared_ptr<Window> window(new Window(_wndproc, _classID, _width, _height, _windowTitle));
	mWindows[_windowid] = window;
	//�E�B���h�E�ɕt������X���b�v�`�F�[���̒ǉ�
	HWND hwnd = window->GetWindowHandle();
	boost::shared_ptr<DX12SwapChain> swapchain = mdx12.CreateSwapChain(hwnd, _width, _height);
	mSwapChains.insert(std::pair<unsigned int,boost::shared_ptr<DX12SwapChain>>(_windowid,swapchain));
	return;
}

void Game::OpenSwapChain(unsigned int _winnum)
{
	//���݃`�F�b�N
	auto itr = mSwapChains.find(_winnum);
	BOOST_ASSERT_MSG(itr != mSwapChains.end(), "unregistered windowID");
	mdx12.OpenRenderTarget(mSwapChains[_winnum]);
	mCurrentSwapChain = _winnum;
}

void Game::CloseSwapChain()
{
	if (mCurrentSwapChain != -1)
	{
		mdx12.CloseRenderTarget(mSwapChains[mCurrentSwapChain]);
		mCurrentSwapChain = -1;
	}
}

//Game::~Game()
//{
//	Shutdown();
//}
//
void Game::Terminate()
{
	terminate_flag_ = true;
}

/// <summary>
/// ���͏���
/// </summary>
void Game::ProcessInput()
{
	mInputSystem.ProcessBeforeUpdate(this);
}

/// <summary>
/// �Q�[���S�̂̍X�V
/// </summary>
void Game::UpdateGame()
{
	mIsSceneChangable = false;
	mCurrentScene->Update(&mInputSystem);
}

/// <summary>
/// �o�͐���
/// </summary>
bool Game::GenerateOutput()
{
	//�T�u�V�X�e���̏o�͏���
	BeforeOutput();
	mCurrentScene->Output();
	if (!AfterOutput())return false;
	if (mPandingScene) {
		DeleteScene(mCurrentScene);
		mCurrentScene = mPandingScene;
		mPandingScene = nullptr;
	}
	mIsSceneChangable = true;
	return true;
}

/// <summary>
/// ���C�����[�v
/// </summary>
void Game::RunLoop()
{
	MSG msg = {};
	//"������"���܂��Ă��鎞��
	double millisec = 0;
	//�E�B���h�E��\�����Ă���
	for (auto itr = mWindows.begin(); itr != mWindows.end(); itr++)
	{
		itr->second->ShowWindow();
	}
	DWORD start = timeGetTime();
	//���b�Z�[�W���[�v
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT)
		{
			break;
		}
		DWORD now = timeGetTime();
		double time = millisec + (double)(now - start);
		if (time < mTimeEps)
		{
			continue;
		}
		if (time > mProcessTimeLimit)
		{
			time = mProcessTimeLimit;
		}
		millisec = time;
		start = now;
		ProcessInput();
		while (millisec > mTimeEps)
		{
			DWORD update_start = timeGetTime();
			UpdateGame();
			DWORD update_end = timeGetTime();
			std::string output("Update Time:");
			output += std::to_string(update_end - update_start);
			Log::OutputTrivial(output);
			millisec -= mTimeEps;
		}
		DWORD output_start = timeGetTime();
		if (!GenerateOutput())return;
		DWORD output_end = timeGetTime();
		std::string output("Output Time:");
		output += std::to_string(output_end - output_start);
		Log::OutputTrivial(output);
		if (terminate_flag_)
		{
			for (auto window : mWindows)
			{
				DestroyWindow(window.second->GetWindowHandle());
			}
		}
	}
}

void Game::BeforeOutput()
{
	//�Ƃ肠���������_�[�^�[�Q�b�g�̃N���A�̂�
	for (auto swapchain : mSwapChains) {
		auto swapp = swapchain.second;
		mdx12.OpenRenderTarget(swapp);
		mdx12.ClearRenderTarget(swapp, 1.0f, 1.0f, 1.0f);
		mdx12.CloseRenderTarget(swapp);
	}
}

bool Game::AfterOutput()
{
	//�S�ẴX���b�v�`�F�[���̃t���b�v
	for (auto itr = mSwapChains.begin(); itr != mSwapChains.end(); itr++)
	{
		mdx12.FlipSwapChain(itr->second);
	}
	return true;
}

void Game::DeleteScene(Scene* _scene)
{
	_scene->mDeleteCheck = true;
	delete _scene;
}

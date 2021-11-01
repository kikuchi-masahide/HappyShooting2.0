#pragma once
#include "DX12/DX12.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "InputSystem.h"
#include "PerformanceProfiler.h"

class Scene;
class Window;

class Game {
public:
	bool Initialize();
	void RunLoop();
	Game();
	/// <summary>
	/// ���t���[������ǂ̃V�[���Ɉڍs���邩�w�肷��D
	/// (���ۂɃV�[�����ς��͎̂��t���[�����炾���C���V�[���̏��������s����̂͌Ăяo�����Ȃ̂�����)
	/// </summary>
	template<class S, class... Args>
	void ChangeScene(Args... _args) {
		if (is_executing_destructor_)
		{
			return;
		}
		if (!mIsSceneChangable) {
			if (mPandingScene != nullptr)DeleteScene(mPandingScene);
			mPandingScene = DBG_NEW S(this, _args...);
		}
		else {
			if (mCurrentScene != nullptr)DeleteScene(mCurrentScene);
			mCurrentScene = DBG_NEW S(this, _args...);
		}
	};
	/// <summary>
	/// ���̃C���X�^���X��_windownum�Ԗڂ̃E�B���h�E�̎Q�Ƃ�Ԃ�
	/// </summary>
	boost::shared_ptr<Window> GetWindow(unsigned int _windownum);
	/// <summary>
	/// �E�B���h�E��Game�ɒǉ�����
	/// </summary>
	/// <param name="_windowid">�E�B���h�EID(�E�B���h�E�C�X���b�v�`�F�[���̎w��ɂ͂���ID���g��)</param>
	void AddWindow(WNDPROC _wndproc, LPCWSTR _classID, int _width, int _height, LPCWSTR _windowTitle, unsigned int _windowid);
	//1�t���[��������̎���
	const double mTimeEps = (double)1000 / (double)60;
	//�O�̏����Ƃ̎��ԍ������̎��Ԃ𒴂����ꍇ���̒l�ɋ�������
	const double mProcessTimeLimit = mTimeEps * 3;
	DX12 mdx12;
	/// <summary>
	/// �O�ɊJ���Ă����X���b�v�`�F�[������C���̃E�B���h�E�ɕt������X���b�v�`�F�[�����J��
	/// </summary>
	void OpenSwapChain(unsigned int _winnum);
	void CloseSwapChain();
	TextureManager mTexManager;
	ShaderManager mShaderManager;
	//~Game();
	//����Output�I����RunLoop��E�o���C�v���O�������I��������
	void Terminate();
	void Shutdown();
	PerformanceProfiler::PerformanceProfiler profiler_;
private:
	void ProcessInput();
	void UpdateGame();
	bool GenerateOutput();
	bool mIsRunning;
	Scene* mCurrentScene;
	Scene* mPandingScene;
	bool mIsSceneChangable;
	std::map<unsigned int, boost::shared_ptr<Window>> mWindows;
	void BeforeOutput();
	bool AfterOutput();
	std::map<unsigned int, boost::shared_ptr<DX12SwapChain>> mSwapChains;
	unsigned int mCurrentSwapChain;
	InputSystem mInputSystem;
	//���̃|�C���^��delete���f�X�g���N�^���Ă�
	void DeleteScene(Scene* _scene);
	bool is_executing_destructor_;
	bool terminate_flag_;
};
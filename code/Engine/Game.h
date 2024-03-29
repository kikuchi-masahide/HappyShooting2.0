#pragma once
#include "DX12/DX12.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "InputSystem.h"
#include "PerformanceProfiler.h"

class Scene;
class Window;

//HACK:初期化処理などもGameで完結させる方が分かりやすいなど，Gameを派生したクラスに実装を乗せる形にした方がベターか?
class Game {
public:
	bool Initialize();
	void RunLoop();
	Game();
	/// <summary>
	/// 次フレームからどのシーンに移行するか指定する．
	/// (実際にシーンが変わるのは次フレームからだが，次シーンの初期化が行われるのは呼び出し時なのが困る)
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
	/// このインスタンスで_windownum番目のウィンドウの参照を返す
	/// </summary>
	boost::shared_ptr<Window> GetWindow(unsigned int _windownum);
	/// <summary>
	/// ウィンドウをGameに追加する
	/// </summary>
	/// <param name="_windowid">ウィンドウID(ウィンドウ，スワップチェーンの指定にはこのIDを使う)</param>
	void AddWindow(WNDPROC _wndproc, LPCWSTR _classID, int _width, int _height, LPCWSTR _windowTitle, unsigned int _windowid);
	//1フレーム当たりの時間
	const double mTimeEps = (double)1000 / (double)60;
	//前の処理との時間差がこの時間を超えた場合この値に矯正する
	const double mProcessTimeLimit = mTimeEps * 3;
	DX12 mdx12;
	/// <summary>
	/// 前に開いていたスワップチェーンを閉じ，このウィンドウに付随するスワップチェーンを開く
	/// </summary>
	void OpenSwapChain(unsigned int _winnum);
	void CloseSwapChain();
	TextureManager mTexManager;
	ShaderManager mShaderManager;
	//~Game();
	//次のOutput終了後RunLoopを脱出し，プログラムを終了させる
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
	//このポインタをdeleteしデストラクタを呼ぶ
	void DeleteScene(Scene* _scene);
	bool is_executing_destructor_;
	bool terminate_flag_;
};
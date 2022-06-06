#include "GameClearUI.h"

#include "../TitleScene/TitleScene.h"
#include "TransGradUIScreen.h"

GameClearUI::GameClearUI(Scene* scene)
	:UIScreen(scene,false,true),
	counter_(-1),image_draw_(scene->mGame,32)
{
}

GameClearUI::~GameClearUI()
{
}

void GameClearUI::Update()
{
	counter_++;
	//240~300tick‚ÅˆÃ“]
	if (counter_ == 240)
	{
		mScene->AddUIScreen<TransGradUIScreen>(false, true, MatVec::Vector4(0.0, 0.0, 0.0, 0.0), MatVec::Vector4(0.0, 0.0, 0.0, 1.0), 60, [](TransGradUIScreen* ui) {});
	}
	//¶‘¶ŽžŠÔ‚Í300tick
	if (counter_ >= 300)
	{
		mScene->mGame.ChangeScene<TitleScene>();
	}
}

void GameClearUI::Output()
{
	//120tick‚©‚¯‚Äƒ¿‚ð0‚©‚ç1‚É
	double alpha = 1.0;
	if (counter_ < 120)
	{
		alpha = (double)counter_ / 120.0;
	}
	mScene->mGame.OpenSwapChain(0);
	image_draw_.Draw(mScene->mGame, 0.0, 200.0, image_width_, image_height_, 0.0, alpha, 900.0, 900.0);
	mScene->mGame.CloseSwapChain();
}

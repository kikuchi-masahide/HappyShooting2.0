#include "GameOverUI.h"

#include "../Engine/Scene.h"
#include "../TitleScene/TitleScene.h"
#include "TransGradUIScreen.h"

GameOverUI::GameOverUI(Scene* scene)
	:UIScreen(scene,false,true),
	counter_(-1),image_draw_(scene->mGame,25)
{
}

GameOverUI::~GameOverUI()
{
}

void GameOverUI::Update()
{
	counter_++;
	if (counter_ == 120)
	{
		mScene->AddUIScreen<TransGradUIScreen>(false, true, MatVec::Vector4(0.0, 0.0, 0.0, 0.0), MatVec::Vector4(0.0, 0.0, 0.0, 1.0), 120, [](TransGradUIScreen* ui) {});
	}
	if (counter_ >= 240)
	{
		mScene->mGame.ChangeScene<TitleScene>();
	}
}

void GameOverUI::Output()
{
	double alpha;
	if (counter_ < 60)
	{
		//‚Ä‚«‚Æ‚¤‚Éƒ¿‚ð0‚©‚ç1‚Ü‚Åã‚°‚é
		alpha = (double)counter_ / 60;
	}
	else {
		alpha = 1.0;
	}
	mScene->mGame.OpenSwapChain(0);
	image_draw_.Draw(mScene->mGame, 0.0, 0.0, image_width_, image_height_, 0.0, alpha, 900.0, 900.0);
	mScene->mGame.CloseSwapChain();

}

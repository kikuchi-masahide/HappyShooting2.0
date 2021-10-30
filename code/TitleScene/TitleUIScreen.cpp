#include "TitleUIScreen.h"

#include "TitleScene.h"
#include "../Engine/Game.h"
#include "../MainScene.h"

TitleUIScreen::TitleUIScreen(Scene* scene)
//下部オブジェクトのアップデートは許可，入力は渡さない
	:UIScreen(scene, false, true), scene_(scene),
	start_button_(this, 0, 1, kStartButtonCenterX_,  kButtonWidth_, kStartButtonCenterY_, kButtonHeight_,
		[](Helpers::HUIButton* button) {
		button->screen_->mScene->mGame.ChangeScene<MainScene>();
	}),
	quit_button_(this, 12, 13, kQuitButtonCenterX_, kButtonWidth_, kQuitButtonCenterY_, kButtonHeight_,
		[](Helpers::HUIButton* button) {
		button->screen_->mScene->mGame.Terminate();
	}),
	title_draw_helper_(scene->mGame, 2)
{
}

void TitleUIScreen::Update()
{
	start_button_.Update();
	quit_button_.Update();
}

void TitleUIScreen::Output()
{
	//ウィンドウのRTVを開く
	scene_->mGame.OpenSwapChain(0);
	//タイトル描画
	title_draw_helper_.DrawCenter(scene_->mGame, kTitleCenterX_, kTitleCenterY_, kTitleWidth_, KTitleHeight_, 900, 900);
	start_button_.Output();
	quit_button_.Output();
	//TODO:血色悪くね?
	scene_->mGame.CloseSwapChain();

}

TitleUIScreen::~TitleUIScreen()
{
}

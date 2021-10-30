#include "stdafx.h"
#include "PauseUIScreen.h"

#include "Scene.h"
#include "Game.h"
#include "code/TitleScene/TitleScene.h"
#include "HBetapaint.h"
#include "TransGradUIScreen.h"

PauseUIScreen::PauseUIScreen(Scene* scene)
	:UIScreen(scene, false, false),
	pause_(scene->mGame, 14),
	resume_button_(this, 15, 16, resume_button_centerx_, resume_button_width_, resume_button_centery_, resume_button_height_, [](Helpers::HUIButton* button) {
	button->screen_->SetDeleteFlag();
}),
back_button_(this, 17, 18, back_button_centerx_, back_button_width_, back_button_centery_, back_button_height_, [](Helpers::HUIButton* button) {
	auto& game = button->screen_->mScene->mGame;
	button->screen_->SetDeleteFlag();
	button->screen_->mScene->AddUIScreen<TransGradUIScreen>(false, false, MatVec::Vector4(0.5, 0.5, 0.5, 0.5), MatVec::Vector4(0.0, 0.0, 0.0, 1.0), 120, [](TransGradUIScreen* uiscreen) {
		uiscreen->mScene->mGame.ChangeScene<TitleScene>();
	});
})
{
}

void PauseUIScreen::Update()
{
	resume_button_.Update();
	back_button_.Update();
	auto esc = mScene->GetKeyState(VK_ESCAPE);
	if (esc == ButtonState::Released)
	{
		SetDeleteFlag();
	}
}

void PauseUIScreen::Output()
{
	HBetapaint::Beta(mScene->mGame, MatVec::Vector4(0.5, 0.5, 0.5, 0.5));
	pause_.DrawCenter(mScene->mGame, pause_text_centerx_, pause_text_centery_, pause_text_width_, pause_text_height_, 900.0, 900.0);
	resume_button_.Output();
	back_button_.Output();
}

PauseUIScreen::~PauseUIScreen()
{
}

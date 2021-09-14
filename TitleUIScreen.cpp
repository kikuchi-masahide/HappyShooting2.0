#include "TitleUIScreen.h"

#include "TitleScene.h"
#include "Game.h"
#include "MainScene.h"

TitleUIScreen::TitleUIScreen(Scene* scene)
//�����I�u�W�F�N�g�̃A�b�v�f�[�g�͋��C���͓͂n���Ȃ�
	:UIScreen(scene, false, true), scene_(scene),
	start_button_(this, 0, 1, kButtonCenterX_,  kButtonWidth_, kButtonCenterY_, kButtonHeight_,
		[](HUIButton* button) {
		button->screen_->mScene->mGame.ChangeScene<MainScene>();
	}),
	title_draw_helper_(scene->mGame, 2)
{
}

void TitleUIScreen::Update()
{
	start_button_.Update();
}

void TitleUIScreen::Output()
{
	//�E�B���h�E��RTV���J��
	scene_->mGame.OpenSwapChain(0);
	//�^�C�g���`��
	title_draw_helper_.DrawCenter(scene_->mGame, kTitleCenterX_, kTitleCenterY_, kTitleWidth_, KTitleHeight_, 900, 900);
	start_button_.Output();
	scene_->mGame.CloseSwapChain();

}

TitleUIScreen::~TitleUIScreen()
{
}

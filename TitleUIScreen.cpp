#include "TitleUIScreen.h"

#include "TitleScene.h"
#include "Game.h"
#include "MainScene.h"

TitleUIScreen::TitleUIScreen(TitleScene* scene)
//�����I�u�W�F�N�g�̃A�b�v�f�[�g�͋��C���͓͂n���Ȃ�
	:UIScreen(false,true),scene_(scene),
	button_draw_helper_away_(scene->mGame,0),button_draw_helper_on_(scene->mGame,1),
	title_draw_helper_(scene->mGame,2),
	cursor_draw_helper_(scene->mGame,3)
{
}

void TitleUIScreen::Update()
{
}

void TitleUIScreen::Output()
{
	static int t = 0;
	//�E�B���h�E��RTV���J��
	scene_->mGame.OpenSwapChain(0);
	//�^�C�g���`��
	title_draw_helper_.DrawCenter(scene_->mGame, kTitleCenterX_, kTitleCenterY_, kTitleWidth_, KTitleHeight_, 900, 900);
	//�}�E�X�ʒu�擾
	auto mouse_pos = scene_->GetMouseClientPos(0);
	//���㌴�_�Ȃ̂�y���W���]
	double mouse_x = mouse_pos(0);
	double mouse_y = mouse_pos(1);
	bool is_mouse_in_button = false;
	//�}�E�X�̈ʒu���{�^�����ł���Ƃ�
	if (
		kButtonCenterX_ - kButtonWidth_ / 2 <= mouse_x &&
		mouse_x <= kButtonCenterX_ + kButtonWidth_ / 2 &&
		kButtonCenterY_ - kButtonHeight_ / 2 <= mouse_y &&
		mouse_y <= kButtonCenterY_ + kButtonHeight_ / 2
		)
	{
		is_mouse_in_button = true;
		//�{�^����\��
		button_draw_helper_on_.DrawCenter(scene_->mGame, kButtonCenterX_, kButtonCenterY_, kButtonWidth_, kButtonHeight_, 900, 900);
	}
	else
	{
		button_draw_helper_away_.DrawCenter(scene_->mGame, kButtonCenterX_, kButtonCenterY_, kButtonWidth_, kButtonHeight_, 900, 900);
	}
	//�}�E�X���{�^���̏��
	auto mouse_left = scene_->GetKeyState(VK_LBUTTON);
	//�{�^�����ō��{�^���𗣂���
	if (is_mouse_in_button && mouse_left == ButtonState::Released)
	{
		TransToMainScene();
	}
	//�J�[�\���`��
	cursor_draw_helper_.DrawCenter(scene_->mGame, mouse_x, mouse_y, 20, 20, 900, 900);
	scene_->mGame.CloseSwapChain();
	t++;
}

TitleUIScreen::~TitleUIScreen()
{
}

void TitleUIScreen::TransToMainScene()
{
	scene_->mGame.ChangeScene<MainScene>();
}


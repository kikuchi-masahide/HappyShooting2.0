#pragma once
#include "../UIScreen.h"
#include "../HTextureDraw.h"
#include "../HTextureAlphaRotateDraw.h"
#include "../HUIButton.h"

class TitleScene;

//�^�C�g����ʗp��UIScreen
class TitleUIScreen :public UIScreen
{
public:
	TitleUIScreen(Scene* scene);
	void Update();
	void Output();
	~TitleUIScreen();
private:
	//�X�^�[�g�{�^��
	const double kStartButtonCenterY_ = -150;
	const double kStartButtonCenterX_ = 0;
	const double kButtonWidth_ = 150;
	const double kButtonHeight_ = 150;
	Helpers::HUIButton start_button_;
	//�I���{�^��
	const double kQuitButtonCenterY_ = -325;
	const double kQuitButtonCenterX_ = 0;
	Helpers::HUIButton quit_button_;
	//�^�C�g���`��̂��߂̏��
	Helpers::HTextureDraw title_draw_helper_;
	const double kTitleCenterY_ = 150;
	const double kTitleCenterX_ = 0;
	const double kTitleWidth_ = 300;
	const double KTitleHeight_ = 30;
	//�eScene�C���X�^���X
	Scene* scene_;
};
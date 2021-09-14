#pragma once
#include "UIScreen.h"
#include "HTextureDraw.h"
#include "HTextureAlphaRotateDraw.h"
#include "HUIButton.h"

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
	//�{�^��
	const double kButtonCenterY_ = -250;
	const double kButtonCenterX_ = 0;
	const double kButtonWidth_ = 200;
	const double kButtonHeight_ = 200;
	HUIButton start_button_;
	//�^�C�g���`��̂��߂̏��
	Helpers::HTextureDraw title_draw_helper_;
	const double kTitleCenterY_ = 150;
	const double kTitleCenterX_ = 0;
	const double kTitleWidth_ = 300;
	const double KTitleHeight_ = 30;
	//�eScene�C���X�^���X
	Scene* scene_;
};
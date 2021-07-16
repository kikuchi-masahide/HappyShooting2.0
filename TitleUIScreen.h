#pragma once
#include "UIScreen.h"
#include "HTextureDraw.h"
#include "HTextureAlphaRotateDraw.h"

class TitleScene;

//�^�C�g����ʗp��UIScreen
class TitleUIScreen :public UIScreen
{
public:
	TitleUIScreen(TitleScene* scene);
	void Update();
	void Output();
	~TitleUIScreen();
private:
	//�{�^���`��̂��߂̏��
	Helpers::HTextureDraw button_draw_helper_away_;
	Helpers::HTextureDraw button_draw_helper_on_;
	const double kButtonCenterY_ = -250;
	const double kButtonCenterX_ = 0;
	const double kButtonWidth_ = 200;
	const double kButtonHeight_ = 200;
	//�^�C�g���`��̂��߂̏��
	Helpers::HTextureDraw title_draw_helper_;
	const double kTitleCenterY_ = 150;
	const double kTitleCenterX_ = 0;
	const double kTitleWidth_ = 300;
	const double KTitleHeight_ = 30;
	//�J�[�\���\��
	Helpers::HTextureDraw cursor_draw_helper_;
	//�eScene�C���X�^���X
	Scene* scene_;
	//MainScene�N���X�ֈڍs���邽�߂̊֐�
	void TransToMainScene();

	Helpers::HTextureAlphaRotateDraw test;
};
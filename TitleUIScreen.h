#pragma once
#include "UIScreen.h"
#include "HTextureDraw.h"

//�^�C�g����ʗp��UIScreen
class TitleUIScreen :public UIScreen
{
public:
	TitleUIScreen(Scene* scene);
	void Update();
	void Output();
	~TitleUIScreen();
private:
	//�{�^���`��̂��߂̏��
	HTextureDraw button_draw_helper_away_;
	HTextureDraw button_draw_helper_on_;
	const double kButtonCenterY_ = 200;
	const double kButtonCenterX_ = 450;
	const double kButtonWidth_ = 200;
	const double kButtonHeight_ = 200;
	//�^�C�g���`��̂��߂̏��
	HTextureDraw title_draw_helper_;
	const double kTitleCenterY_ = 600;
	const double kTitleCenterX_ = 450;
	const double kTitleWidth_ = 300;
	const double KTitleHeight_ = 30;
	//�J�[�\���\��
	HTextureDraw cursor_draw_helper_;
	//�eScene�C���X�^���X
	Scene* scene_;
	//MainScene�N���X�ֈڍs���邽�߂̊֐�
	void TransToMainScene();
};
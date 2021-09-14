#pragma once
#include "UIScreen.h"
#include "HTextureDraw.h"
#include "HTextureAlphaRotateDraw.h"
#include "HUIButton.h"

class TitleScene;

//タイトル画面用のUIScreen
class TitleUIScreen :public UIScreen
{
public:
	TitleUIScreen(Scene* scene);
	void Update();
	void Output();
	~TitleUIScreen();
private:
	//ボタン
	const double kButtonCenterY_ = -250;
	const double kButtonCenterX_ = 0;
	const double kButtonWidth_ = 200;
	const double kButtonHeight_ = 200;
	HUIButton start_button_;
	//タイトル描画のための情報
	Helpers::HTextureDraw title_draw_helper_;
	const double kTitleCenterY_ = 150;
	const double kTitleCenterX_ = 0;
	const double kTitleWidth_ = 300;
	const double KTitleHeight_ = 30;
	//親Sceneインスタンス
	Scene* scene_;
};
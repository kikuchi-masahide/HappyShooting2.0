#pragma once
#include "UIScreen.h"
#include "HTextureDraw.h"
#include "HTextureAlphaRotateDraw.h"

class TitleScene;

//タイトル画面用のUIScreen
class TitleUIScreen :public UIScreen
{
public:
	TitleUIScreen(TitleScene* scene);
	void Update();
	void Output();
	~TitleUIScreen();
private:
	//ボタン描画のための情報
	Helpers::HTextureDraw button_draw_helper_away_;
	Helpers::HTextureDraw button_draw_helper_on_;
	const double kButtonCenterY_ = -250;
	const double kButtonCenterX_ = 0;
	const double kButtonWidth_ = 200;
	const double kButtonHeight_ = 200;
	//タイトル描画のための情報
	Helpers::HTextureDraw title_draw_helper_;
	const double kTitleCenterY_ = 150;
	const double kTitleCenterX_ = 0;
	const double kTitleWidth_ = 300;
	const double KTitleHeight_ = 30;
	//カーソル表示
	Helpers::HTextureDraw cursor_draw_helper_;
	//親Sceneインスタンス
	Scene* scene_;
	//MainSceneクラスへ移行するための関数
	void TransToMainScene();

	Helpers::HTextureAlphaRotateDraw test;
};
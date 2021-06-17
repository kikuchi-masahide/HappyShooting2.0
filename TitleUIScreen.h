#pragma once
#include "UIScreen.h"
#include "HTextureDraw.h"

//タイトル画面用のUIScreen
class TitleUIScreen :public UIScreen
{
public:
	TitleUIScreen(Scene* scene);
	void Update();
	void Output();
	~TitleUIScreen();
private:
	//ボタン描画のための情報
	HTextureDraw button_draw_helper_away_;
	HTextureDraw button_draw_helper_on_;
	const double kButtonCenterY_ = 200;
	const double kButtonCenterX_ = 450;
	const double kButtonWidth_ = 200;
	const double kButtonHeight_ = 200;
	//タイトル描画のための情報
	HTextureDraw title_draw_helper_;
	const double kTitleCenterY_ = 600;
	const double kTitleCenterX_ = 450;
	const double kTitleWidth_ = 300;
	const double KTitleHeight_ = 30;
	//カーソル表示
	HTextureDraw cursor_draw_helper_;
	//親Sceneインスタンス
	Scene* scene_;
	//MainSceneクラスへ移行するための関数
	void TransToMainScene();
};
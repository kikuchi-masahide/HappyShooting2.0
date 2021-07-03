#include "stdafx.h"
#include "MainSceneUIScreen.h"

#include "MainScene.h"

MainSceneUIScreen::MainSceneUIScreen(MainScene* scene)
	:UIScreen(true, true),
	cursor_draw_(scene->mGame, 3),point_frame_(scene->mGame),
	scene_(scene)
{
}

void MainSceneUIScreen::Update()
{
}

void MainSceneUIScreen::Output()
{
	Game& game = scene_->mGame;

	//RTVオープン
	game.OpenSwapChain(0);

	//カーソル描画
	auto cursor = scene_->GetMouseClientPos(0);
	cursor -= MatVec::Vector2(450, 450);
	cursor_draw_.DrawCenter(game, cursor(0), cursor(1), 20, 20, 900, 900);

	//ポイント表示枠描画
	point_frame_.DrawFrame(game, point_frame_cx_, point_frame_cy_, point_frame_width_, point_frame_height_, 0.0, 900, 900);

	//RTVクローズ
	scene_->mGame.CloseSwapChain();
}

MainSceneUIScreen::~MainSceneUIScreen()
{
}

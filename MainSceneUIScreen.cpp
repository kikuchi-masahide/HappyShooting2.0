#include "stdafx.h"
#include "MainSceneUIScreen.h"

#include "MainScene.h"

MainSceneUIScreen::MainSceneUIScreen(Scene* scene, boost::shared_ptr<ScoreManager> score_manager)
	:UIScreen(scene, true, true),
	point_frame_(scene->mGame),score_text_draw_(scene->mGame,5),
	number_draw_(scene->mGame,font_size_,MatVec::Vector2(score_leftup_x_,score_leftup_y_),900,900,8),
	score_manager_(score_manager)
{
}

void MainSceneUIScreen::Update()
{
}

void MainSceneUIScreen::Output()
{
	Game& game = mScene->mGame;

	//RTV�I�[�v��
	game.OpenSwapChain(0);

	//�|�C���g�\���g�`��
	point_frame_.DrawFrame(game, point_frame_cx_, point_frame_cy_, point_frame_width_, point_frame_height_, 0.0, 900, 900);
	//Score:�����\��
	score_text_draw_.DrawInRect(
		game, score_image_lux_, score_image_lux_ + score_image_width_, score_image_luy_-score_image_height_, score_image_luy_, 900, 900
	);
	//�X�R�A�\��
	int score = score_manager_->GetScore();
	number_draw_.DrawNumber(game, score);

	//RTV�N���[�Y
	mScene->mGame.CloseSwapChain();
}

MainSceneUIScreen::~MainSceneUIScreen()
{
}

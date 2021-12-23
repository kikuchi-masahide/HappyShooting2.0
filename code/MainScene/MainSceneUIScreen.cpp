#include "MainSceneUIScreen.h"

#include "MainScene.h"
#include "PauseUIScreen.h"

MainSceneUIScreen::MainSceneUIScreen(Scene* scene, boost::shared_ptr<ScoreManager> score_manager)
	:UIScreen(scene, true, true),
	point_frame_(scene->mGame),score_text_draw_(scene->mGame,5),
	number_draw_(scene->mGame,font_size_,MatVec::Vector2(score_leftup_x_,score_leftup_y_),900,900,8),
	score_manager_(score_manager),heart_(scene->mGame,24,heart_height_,heart_height_)
{
}

void MainSceneUIScreen::Update()
{
	//Esc�������ꂽ��|�[�Y�ɔ��
	auto esc = mScene->GetKeyState(VK_ESCAPE);
	if (esc == ButtonState::Released)
	{
		mScene->AddUIScreen<PauseUIScreen>();
	}
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
	//�c�@��
	int life = max(0, score_manager_->GetRemainingLife());
	double heart_cy = heart_by_ + heart_height_ / 2;
	double heart_cx = heart_lx_ + heart_height_ * life / 2;
	heart_.Draw(game, MatVec::Vector2(heart_cx, heart_cy), heart_height_ * life, heart_height_, 1.0, 900.0, 900.0);

	//RTV�N���[�Y
	mScene->mGame.CloseSwapChain();
}

MainSceneUIScreen::~MainSceneUIScreen()
{
}

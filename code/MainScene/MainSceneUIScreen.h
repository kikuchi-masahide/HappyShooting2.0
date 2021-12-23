#pragma once
#include "../Engine/UIScreen.h"
#include "../Helper/HTextureDraw.h"
#include "../Helper/HDrawLineFrame.h"
#include "../Helper/HNumberDraw.h"
#include "../Helper/HSquareRepeatPattern.h"

class ScoreManager;

class MainSceneUIScreen :
    public UIScreen
{
public:
    MainSceneUIScreen(Scene* scene, boost::shared_ptr<ScoreManager> score_manager);
    void Update() override;
    void Output() override;
    ~MainSceneUIScreen();
private:
    //�uScore:�v�̉摜�\��
    Helpers::HTextureDraw score_text_draw_;
    //���_�\���g
    Helpers::HDrawLineFrame point_frame_;
    //���_�\���g�̒��Sx
    constexpr static double point_frame_cx_ = 750-450;
    //���_�\���g�̒��Sy
    constexpr static double point_frame_cy_ = 775-450;
    //���_�\���g�̕�
    constexpr static double point_frame_width_ = 300 - 2;
    //���_�\���g�̍���
    constexpr static double point_frame_height_ = 250 - 2;
    //�uScore:�v�摜�̕�
    constexpr static unsigned int score_image_width_ = 80;
    constexpr static unsigned int score_image_height_ = 30;
    //�uScore:�v�摜�̕\�����W
    constexpr static unsigned int score_image_lux_ = 600 + 20 - 450;
    constexpr static unsigned int score_image_luy_ = 900 - 20 - 450;
    //�X�R�A�\���p
    Helpers::HNumberDraw number_draw_;
    //�X�R�A�\�����W
    constexpr static double score_leftup_x_ = score_image_lux_;
    constexpr static double score_leftup_y_ = score_image_luy_ - score_image_height_;
    //�t�H���g�T�C�Y
    constexpr static double font_size_ = 24.0;
    //�n�[�g�̐����`�摜�̈��
    constexpr static double heart_height_ = 40.0;
    //�n�[�g�\���ʒu(��x�C��y)
    constexpr static double heart_lx_ = score_image_lux_;
    constexpr static double heart_by_ = score_leftup_y_ - font_size_ - 5.0 - heart_height_;
    //�n�[�g�`��p
    Helpers::HSquareRepeatPattern heart_;
    boost::shared_ptr<ScoreManager> score_manager_;
};


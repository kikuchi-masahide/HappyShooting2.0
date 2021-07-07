#pragma once
#include "UIScreen.h"
#include "HTextureDraw.h"
#include "HDrawLineFrame.h"

class MainScene;

class MainSceneUIScreen :
    public UIScreen
{
public:
    MainSceneUIScreen(MainScene* scene);
    void Update() override;
    void Output() override;
    ~MainSceneUIScreen();
private:
    HTextureDraw cursor_draw_;
    //�uScore:�v�̉摜�\��
    HTextureDraw score_text_draw_;
    //���_�\���g
    HDrawLineFrame point_frame_;
    MainScene* scene_;
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
};


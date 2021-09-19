#pragma once
#include "UIScreen.h"

#include "HTextureDraw.h"
#include "HUIButton.h"

class PauseUIScreen :
    public UIScreen
{
public:
    PauseUIScreen(Scene* scene);
    void Update() override;
    void Output() override;
    ~PauseUIScreen();
private:
    Helpers::HTextureDraw pause_;
    Helpers::HUIButton resume_button_;
    Helpers::HUIButton back_button_;
    //Pauseの文字の位置
    static constexpr double pause_text_centerx_ = 0.0;
    static constexpr double pause_text_centery_ = 150.0;
    static constexpr double pause_text_width_ = 300.0;
    static constexpr double pause_text_height_ = 80.0;
    //Resumeボタンの位置
    static constexpr double resume_button_centerx_ = 0.0;
    static constexpr double resume_button_centery_ = -150.0;
    static constexpr double resume_button_width_ = 150.0;
    static constexpr double resume_button_height_ = 150.0;
    //Back to Titleボタンの位置
    static constexpr double back_button_centerx_ = 0.0;
    static constexpr double back_button_centery_ = -325.0;
    static constexpr double back_button_width_ = 150.0;
    static constexpr double back_button_height_ = 150.0;
};


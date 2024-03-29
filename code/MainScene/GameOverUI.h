#pragma once
#include "../Engine/UIScreen.h"

#include "../Helper/HTextureAlphaRotateDraw.h"

class GameOverUI :
    public UIScreen
{
public:
    GameOverUI(Scene* scene);
    ~GameOverUI();
    void Update() override;
    void Output() override;
private:
    //はじめてOutputが呼び出されたとき0
    int counter_;
    static constexpr double image_width_ = 320.0;
    static constexpr double image_height_ = 60.0;
    Helpers::HTextureAlphaRotateDraw image_draw_;
};


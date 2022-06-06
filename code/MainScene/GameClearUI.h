#pragma once
#include "../Engine/UIScreen.h"

#include "../Helper/HTextureAlphaRotateDraw.h"

class GameClearUI :
    public UIScreen
{
public:
    GameClearUI(Scene* scene);
    ~GameClearUI();
    void Update() override;
    void Output() override;
private:
    int counter_;
    static constexpr double image_width_ = 320.0;
    static constexpr double image_height_ = 60.0;
    Helpers::HTextureAlphaRotateDraw image_draw_;
};


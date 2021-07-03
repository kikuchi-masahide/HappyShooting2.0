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
    //得点表示枠
    HDrawLineFrame point_frame_;
    MainScene* scene_;
    //得点表示枠の中心x
    constexpr static double point_frame_cx_ = 750-450;
    //得点表示枠の中心y
    constexpr static double point_frame_cy_ = 775-450;
    //得点表示枠の幅
    constexpr static double point_frame_width_ = 300 - 2;
    //得点表示枠の高さ
    constexpr static double point_frame_height_ = 250 - 2;
};


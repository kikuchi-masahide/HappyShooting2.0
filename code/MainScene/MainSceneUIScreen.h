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
    //「Score:」の画像表示
    Helpers::HTextureDraw score_text_draw_;
    //得点表示枠
    Helpers::HDrawLineFrame point_frame_;
    //得点表示枠の中心x
    constexpr static double point_frame_cx_ = 750-450;
    //得点表示枠の中心y
    constexpr static double point_frame_cy_ = 775-450;
    //得点表示枠の幅
    constexpr static double point_frame_width_ = 300 - 2;
    //得点表示枠の高さ
    constexpr static double point_frame_height_ = 250 - 2;
    //「Score:」画像の幅
    constexpr static unsigned int score_image_width_ = 80;
    constexpr static unsigned int score_image_height_ = 30;
    //「Score:」画像の表示座標
    constexpr static unsigned int score_image_lux_ = 600 + 20 - 450;
    constexpr static unsigned int score_image_luy_ = 900 - 20 - 450;
    //スコア表示用
    Helpers::HNumberDraw number_draw_;
    //スコア表示座標
    constexpr static double score_leftup_x_ = score_image_lux_;
    constexpr static double score_leftup_y_ = score_image_luy_ - score_image_height_;
    //フォントサイズ
    constexpr static double font_size_ = 24.0;
    //ハートの正方形画像の一辺
    constexpr static double heart_height_ = 40.0;
    //ハート表示位置(左x，下y)
    constexpr static double heart_lx_ = score_image_lux_;
    constexpr static double heart_by_ = score_leftup_y_ - font_size_ - 5.0 - heart_height_;
    //ハート描画用
    Helpers::HSquareRepeatPattern heart_;
    boost::shared_ptr<ScoreManager> score_manager_;
};


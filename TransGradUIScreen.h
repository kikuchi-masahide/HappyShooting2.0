#pragma once
#include "code/Engine/UIScreen.h"
#include "code/Engine/Math/Math.h"

/// <summary>
/// 画面全体でリニアなグラデーション変化をするUIScreen
/// </summary>
class TransGradUIScreen :
    public UIScreen
{
public:
    /// <param name="start">グラデーション始めの色</param>
    /// <param name="end">グラデーション終わりの色</param>
    /// <param name="time">全体で何tickのグラデーションを行うか</param>
    /// <param name="terminate">グラデーション終了tickの処理</param>
    TransGradUIScreen(Scene* scene,bool input,bool update,MatVec::Vector4 start, MatVec::Vector4 end, unsigned int time, std::function<void(TransGradUIScreen*)> terminate);
    ~TransGradUIScreen();
    void Update() override;
    void Output() override;
private:
    MatVec::Vector4 start_;
    MatVec::Vector4 end_;
    unsigned int time_;
    unsigned int counter_;
    std::function<void(TransGradUIScreen*)> terminate_;
};

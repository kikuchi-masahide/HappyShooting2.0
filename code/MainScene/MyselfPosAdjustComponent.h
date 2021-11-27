#pragma once
#include "../Engine/Component.h"

#include "../Engine/Math/Math.h"

//自機の位置を，直線の右側領域に収まるよう修正する
class MyselfPosAdjustComponent :
    public Component
{
public:
    /// <summary>
    /// 点a，bを通る直線の，ベクトルb-aの右側の領域に収まるよう，自機の位置を修正する
    /// </summary>
    /// <param name="myself">自機ハンドル</param>
    MyselfPosAdjustComponent(GameObjectHandle handle, GameObjectHandle myself, MatVec::Vector2 a, MatVec::Vector2 b);
    ~MyselfPosAdjustComponent();
    void Update() override;
    //直線の通る点を修正する
    void SetAnchorPoint(MatVec::Vector2 a, MatVec::Vector2 b);
private:
    MatVec::Vector2 a_, b_;
    GameObjectHandle myself_;
};


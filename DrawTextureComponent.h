#pragma once
#include "MainSceneDrawComponent.h"

#include "code/Helper/HTextureAlphaRotateDraw.h"
#include "code/Engine/GameObject.h"

/// <summary>
/// テクスチャを描画するコンポーネント
/// </summary>
class DrawTextureComponent :
    public MainSceneDrawComponent
{
public:
    DrawTextureComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, unsigned int texture_id,double z);
    virtual void Draw();
    //描画中心の，オブジェクトの中心座標からのオフセット
    MatVec::Vector2 center_offset_;
    //オブジェクトの角度からの，描画角度のオフセット
    double angle_offset_;
    //不透明度(0.0~1.0)
    double alpha_;
    //描画幅
    double width_;
    //描画高さ
    double height_;
private:
    Helpers::HTextureAlphaRotateDraw draw_helper_;
};


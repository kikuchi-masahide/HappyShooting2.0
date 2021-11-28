#include "MainSceneShrinkLayer_header.hlsli"

//このuv座標の点を描画すべきか否か
bool IsValid(float2 uv)
{
    uv.x = (uv.x - 0.5) * 600.0;
    uv.y = (0.5 - uv.y) * 900.0;
    
    //anchor_[0]->anchor_[1]
    {
        //anchor_[0]を原点とする平行移動
        float x = uv.x - anchor_0_.x;
        float y = uv.y - anchor_0_.y;
        //線分がx軸となす角度
        float theta = atan2(anchor_1_.y - anchor_0_.y, anchor_1_.x - anchor_0_.x);
        //anchor_[0]->anchor_[1]がx軸になるよう回転したときのy座標
        float ny = -x * sin(theta) + y * cos(theta);
        //左側 <==> y > 0
        if(ny > 0)
        {
            return false;
        }
    }
    //anchor_[1]->anchor_[2]
    {
        //anchor_[1]を原点とする平行移動
        float x = uv.x - anchor_1_.x;
        float y = uv.y - anchor_1_.y;
        //線分がx軸となす角度
        float theta = atan2(anchor_2_.y - anchor_1_.y, anchor_2_.x - anchor_1_.x);
        //anchor_[1]->anchor_[2]がx軸になるよう回転したときのy座標
        float ny = -x * sin(theta) + y * cos(theta);
        //左側 <==> y > 0
        if (ny > 0)
        {
            return false;
        }
    }
    //anchor_[2]->anchor_[3]
    {
        //anchor_[2]を原点とする平行移動
        float x = uv.x - anchor_2_.x;
        float y = uv.y - anchor_2_.y;
        //線分がx軸となす角度
        float theta = atan2(anchor_3_.y - anchor_2_.y, anchor_3_.x - anchor_2_.x);
        //anchor_[2]->anchor_[3]がx軸になるよう回転したときのy座標
        float ny = -x * sin(theta) + y * cos(theta);
        //左側 <==> y > 0
        if (ny > 0)
        {
            return false;
        }
    }
    //anchor_[3]->anchor_[0]
    {
        //anchor_[3]を原点とする平行移動
        float x = uv.x - anchor_3_.x;
        float y = uv.y - anchor_3_.y;
        //線分がx軸となす角度
        float theta = atan2(anchor_0_.y - anchor_3_.y, anchor_0_.x - anchor_3_.x);
        //anchor_[3]->anchor_[0]がx軸になるよう回転したときのy座標
        float ny = -x * sin(theta) + y * cos(theta);
        //左側 <==> y > 0
        if (ny > 0)
        {
            return false;
        }
    }
    return true;
}

float4 main(Output output) : SV_Target
{
    if (!IsValid(output.uv_))
    {
        discard;
    }
    return tex.Sample(smp, output.uv_);
}
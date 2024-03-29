#include "DrawLazerComponent_header.hlsli"

float4 main(Output input):SV_Target
{
    //線分の端点は(length_/2,0)と(-length_/2,0)
    float2 uv = input.uv;
    float l;   //線分からの距離
    if (uv.x > length_/2)
    {
        l = sqrt((uv.x - length_ / 2) * (uv.x - length_ / 2) + uv.y * uv.y);
        if(l > r_)
        {
            l = 0.0;
        }
    }
    else if(uv.x < -length_/2)
    {
        l = sqrt((uv.x + length_ / 2) * (uv.x + length_ / 2) + uv.y * uv.y);
        if(l > r_)
        {
            l = 0.0;
        }
    }
    else
    {
        l = abs(uv.y);
    }
    return float4(1.0, 0.0, 0.0, l / r_);
}
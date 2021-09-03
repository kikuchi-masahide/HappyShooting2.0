#include "DrawLazerComponent_header.hlsli"

float4 main(Output input):SV_Target
{
    //�����̒[�_��(length_/2,0)��(-length_/2,0)
    float2 uv = input.uv;
    float l;   //��������̋���
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
#include "MainSceneClippingLayer_header.hlsli"

float4 main(Output output) : SV_TARGET
{
    float4 uv_full = float4(output.uv_, 0.0f, 1.0f);
    uv_full = mul(uv_full, uv_exp_);
    uv_full /= uv_full.w;
    float d = distance(myself_, float2(uv_full.x, uv_full.y));
    if (d > r_)
    {
        return float4(0.0f, 0.0f, 0.0f, 1.0f);
    }
    else
    {
        return tex.Sample(smp, output.uv_);
    }

}
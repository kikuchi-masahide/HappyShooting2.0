#include "MainSceneFlippingLayer_header.hlsli"

float4 main(Output output) : SV_Target
{
    float4 color0 = tex.Sample(smp, output.uv_);
    color0.x = 1.0f - color0.x;
    color0.y = 1.0f - color0.y;
    color0.z = 1.0f - color0.z;
    return color0;
}
#include "MainSceneEndingLayer_header.hlsli"

float4 main(Output output) : SV_TARGET
{
    float dx = centerx - output.clipos_.x;
    float dy = centery - output.clipos_.y;
    float d = sqrt(dx * dx + dy * dy);
    float ar;
    if(d <= r1)
    {
        ar = (1.0 - d / r1) * r1alphast + d * r1alphaen / r1;
    }
    else if(d <= r2)
    {
        ar = (r2alphaen * (d - r1) + r2alphast * (r2 - d)) / (r2 - r1);
    }
    else
    {
        ar = 1.0f;
    }
    float4 sm = tex.Sample(smp, output.uv_); 
    return float4(sm.xyz,sm.w*ar);
    //return float4(ar, 0.0, 0.0, 1.0);
}
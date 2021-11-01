#include "DrawNormalBulletComponentHeader.hlsli"

float4 main(Output input) : SV_TARGET
{
    float4 texcolor = tex.Sample(smp, input.uv);
    return float4(rgb_, alpha_) * texcolor.w;

}
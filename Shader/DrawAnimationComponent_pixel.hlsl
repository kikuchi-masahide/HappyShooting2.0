#include "DrawAnimationComponent_header.hlsli"

float4 main(Output input):SV_Target
{
    float4 color = tex.Sample(smp, input.uv);
    return color;
}
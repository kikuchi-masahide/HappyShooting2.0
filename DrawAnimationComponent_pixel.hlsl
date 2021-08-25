#include "DrawAnimationComponent_header.hlsli"

float4 main(Output input):SV_Target
{
    return tex.Sample(smp, input.uv);
}
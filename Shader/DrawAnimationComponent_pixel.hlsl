#include "DrawAnimationComponent_header.hlsli"

float4 main(Output input):SV_Target
{
    float3 color = tex.Sample(smp, input.uv).xyz;
    float alpha = tex.Sample(smp, input.uv).w;
    alpha *= alpha_;
    return float4(color,alpha);
}
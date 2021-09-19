#include "HBetapaint_header.hlsli"

float4 main(float4 pos:SV_Position):SV_Target
{
    float4 color = float4(rgb_, alpha_);
    return color;
}
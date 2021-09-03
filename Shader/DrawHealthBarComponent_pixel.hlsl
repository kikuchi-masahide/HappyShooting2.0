#include "DrawHealthBarComponent_header.hlsli"

float4 main(Output input) : SV_TARGET
{
    float r = input.uv_.x;
    if (r <= r_)
    {
        return float4(0.0, 1.0, 0.0, 0.5);
    }
    return float4(1.0, 1.0, 1.0, 0.0);
}
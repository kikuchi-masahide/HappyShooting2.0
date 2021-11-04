#include "MainSceneClippingLayer_header.hlsli"

Output main( float4 pos : POSITION ,float2 uv : TEXCOORD)
{
    Output output;
    output.svpos_ = mul(pos, mat_);
    output.uv_ = uv;
    return output;
}
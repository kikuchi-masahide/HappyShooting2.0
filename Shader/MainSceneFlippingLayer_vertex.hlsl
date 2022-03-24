#include "MainSceneFlippingLayer_header.hlsli"

Output main( float4 pos_ : POSITION, float2 uv_ : TEXCOORD)
{
    Output output;
    output.svpos_ = pos_;
    output.uv_ = uv_;
    return output;
}
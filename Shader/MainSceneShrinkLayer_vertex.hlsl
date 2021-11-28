#include "MainSceneShrinkLayer_header.hlsli"

Output main( float4 pos_ : POSITION, float2 uv_ : TEXCOORD )
{
    Output output;
    output.svpos_ = mul(pos_, mat_);
    output.uv_ = uv_;
    return output;
}
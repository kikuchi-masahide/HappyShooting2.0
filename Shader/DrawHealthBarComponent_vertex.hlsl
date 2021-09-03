#include "DrawHealthBarComponent_header.hlsli"

Output main( float4 pos : POSITION,float2 uv:TEXCOORD )
{
    Output output;
    output.svpos_ = mul(pos, expand_);
    output.svpos_ = mul(output.svpos_, translate_);
    output.svpos_ = mul(output.svpos_, ortho_);
    output.uv_ = uv;
    return output;
}
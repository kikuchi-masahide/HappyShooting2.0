#include "DrawAnimationComponent_header.hlsli"

Output main(float4 pos:POSITION,float2 uv:TEXCOORD)
{
    Output output;
    output.svpos = mul(pos, pos_matrix_);
    output.uv = mul(uv, uv_matrix_);
    return output;
}
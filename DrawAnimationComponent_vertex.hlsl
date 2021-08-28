#include "DrawAnimationComponent_header.hlsli"

Output main(float4 pos:POSITION,float2 uv:TEXCOORD)
{
    Output output;
    output.svpos = mul(pos, pos_matrix_);
    output.uv.x = uv_x_ + uv.x * uv_w_;
    output.uv.y = uv_y_ + uv.y * uv_h_;
    return output;
}
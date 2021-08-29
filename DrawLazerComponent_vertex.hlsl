#include "DrawLazerComponent_header.hlsli"

Output main(float4 pos_:POSITION,float2 uv_:TEXCOORD)
{
    Output output;
    output.svpos = mul(pos_, expand_matrix_);
    output.svpos = mul(output.svpos, pos_matrix_);
    float4 uv4 = float4(uv_.x, uv_.y, 0.0f, 0.0f);
    float4 uv4_exp = mul(uv4, expand_matrix_);
    output.uv = float2(uv4_exp.x, uv4_exp.y);
    return output;
}
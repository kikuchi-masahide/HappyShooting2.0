cbuffer cbuff0 : register(b0)
{
    matrix expand_matrix_;
    matrix pos_matrix_;
    float length_;
    float r_;
}

struct Output
{
    float4 svpos : SV_POSITION;
    float2 uv : TEXCOORD;
};
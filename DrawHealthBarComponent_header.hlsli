cbuffer cbuff0 : register(b0)
{
    matrix expand_;
    matrix translate_;
    matrix ortho_;
    float r_;
};

struct Output
{
    float4 svpos_ : SV_Position;
    float2 uv_ : TEXCOORD;
};
cbuffer cbuff0 : register(b0)
{
    matrix pos_matrix_;
    matrix uv_matrix_;
}

struct Output
{
    float4 svpos : SV_POSITION;
    float2 uv : TEXCOORD;
};

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);
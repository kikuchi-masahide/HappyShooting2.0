Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);
cbuffer cbuff0 : register(b0)
{
    float r1;
    float r2;
    float r1alphast;
    float r1alphaen;
    float r2alphast;
    float r2alphaen;
    float centerx;
    float centery;
}

struct Output
{
    float4 svpos_ : SV_POSITION;
    float2 uv_ : TEXCOORD;
    float2 clipos_ : CLIPOSITION;
};
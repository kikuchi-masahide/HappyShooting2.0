Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);
cbuffer cbuff0 : register(b0)
{
    matrix mat_;
    //TODO:anchor_[n]‚ÅŽó‚¯“n‚µ‚µ‚½‚ç‚¨‚©‚µ‚­‚È‚Á‚½ ?
    float2 anchor_0_;
    float2 anchor_1_;
    float2 anchor_2_;
    float2 anchor_3_;
}

struct Output
{
    float4 svpos_ : SV_POSITION;
    float2 uv_ : TEXCOORD;
};
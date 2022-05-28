#include "MainSceneEndingLayer_header.hlsli"

Output main(float4 pos:POSITION,float2 uv:TEXCOORD,float2 clipos:CLIPOSITION)
{
    Output output;
    output.svpos_ = pos;
    output.uv_ = uv;
    output.clipos_ = clipos;
    return output;
}
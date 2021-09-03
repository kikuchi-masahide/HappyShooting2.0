#include "HNumberDraw_header.hlsli"

float4 main(Output input) : SV_TARGET
{
	float4 color = tex.Sample(smp,input.uv_);
	return color;
}
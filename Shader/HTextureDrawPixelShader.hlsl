#include "HTextureDrawInclude.hlsli"

float4 main(Output input) : SV_TARGET
{
	float4 color = tex.Sample(smp,input.uv);
	return float4(color);
}
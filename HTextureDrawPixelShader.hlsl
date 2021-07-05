#include "HTextureDrawInclude.hlsli"

float4 main(Output input) : SV_TARGET
{
	float4 color = tex.Sample(smp,input.uv);
	if (color.a == 0)
	{
		discard;
	}
	return float4(color);
}
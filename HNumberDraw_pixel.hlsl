#include "HNumberDraw_header.hlsli"

float4 main(Output input) : SV_TARGET
{
	float4 color = tex.Sample(smp,input.uv_);
	if (color.a == 0)
	{
		discard;
	}
	return color;
}
#include "HTextureAlphaRotateDrawHeader.hlsli"

float4 main(Output input) : SV_TARGET
{
	float3 tex_xyz = tex.Sample(smp,input.uv).xyz;
	float tex_w = tex.Sample(smp, input.uv).w;
	tex_w *= alpha;
	//return float4(tex_xyz, tex_w);
	return float4(1.0, 0.0, 0.0, 1.0);
}
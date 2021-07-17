#include "HTextureDrawInclude.hlsli"

Output main( float4 pos : POSITION,float2 uv : TEXCOORD )
{
	Output output;
	output.svpos = mul(pos, mat);
	output.uv = uv;
	return output;
}
#include "HTextureDrawInclude.hlsli"

Output main( float4 pos : POS,float2 uv : UV )
{
	Output output;
	output.svpos = mul(mat, pos);
	output.uv = uv;
	return output;
}
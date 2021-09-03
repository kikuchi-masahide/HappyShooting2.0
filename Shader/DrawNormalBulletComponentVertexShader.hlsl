#include "DrawNormalBulletComponentHeader.hlsli"

Output main( float4 pos : POSITION,float2 uv:TEXCOORD )
{
	Output output;
	output.svpos = mul(pos,mat_);
	output.uv = uv;
	return output;
}
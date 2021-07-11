#include "DrawDeathEffectComponent_header.hlsli"

Output main( float4 pos : POSITION ,float2 uv:TEXCOORD)
{
	Output output;
	output.svpos_ = mul(pos, exp_);
	output.svpos_ = mul(output.svpos_, trans_ortho_);
	float4 uv00 = float4(uv, 0, 0);
	uv00 = mul(uv00, exp_);
	output.uv_.x = uv00.x;
	output.uv_.y = uv00.y;
	return output;
}
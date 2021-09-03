#include "HNumberDraw_header.hlsli"

Output main( float4 pos : POSITION, float2 uv : TEXCOORD, unsigned int pos_left : LEFT_INDEX)
{
	Output output;
	output.svpos_ = mul(pos, mat);
	if (pos_left < 4) {
		output.uv_.x = (uv.x + index0[pos_left]) / 12;
	}
	else {
		output.uv_.x = (uv.x + index1[pos_left - 4]) / 12;
	}
	output.uv_.y = uv.y;
	return output;
}
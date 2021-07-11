#include "DrawDeathEffectComponent_header.hlsli"

float4 main(Output input) : SV_TARGET
{
	float d2 = input.uv_.x * input.uv_.x + input.uv_.y * input.uv_.y;
	float d = sqrt(d2);
	float r = d / radius_;
	clip(1.0f-r);
	clip(r - 0.75f);
	float s = 4.0f * (1.0f - r);
	return float4(s, s, s, alpha_);
}
#include "DrawNormalBulletComponentHeader.hlsli"

float4 main(Output input) : SV_TARGET
{
	float u = input.uv.x;
	float v = input.uv.y;
	//‰~’†S‚©‚ç‚±‚Ì“_‚Ü‚Å‚Ì‹——£(uvÀ•W‚Å)
	float d = sqrt((u - 0.5) * (u - 0.5) + (v - 0.5) * (v - 0.5));
	//‰~ŠO
	if (d > 0.5)
	{
		return float4(0.0, 0.0, 0.0, 0.0);
	}
	//‹——£‚ğŠ„‡‚É’¼‚·(‰~ü->1.0,’†S->0.0)
	d /= 0.5;
	return float4(r_, g_, b_, alpha_ * d);
}
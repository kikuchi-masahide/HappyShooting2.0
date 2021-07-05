#include "DrawNormalBulletComponentHeader.hlsli"

float4 main(Output input) : SV_TARGET
{
	float u = input.uv.x;
	float v = input.uv.y;
	//円中心からこの点までの距離(uv座標で)
	float d = sqrt((u - 0.5) * (u - 0.5) + (v - 0.5) * (v - 0.5));
	//円外
	if (d > 0.5)
	{
		discard;
	}
	//距離を割合に直す(円周->1.0,中心->0.0)
	d /= 0.5;
	return float4(rgb_, alpha_ * d);
}
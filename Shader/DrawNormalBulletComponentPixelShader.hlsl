#include "DrawNormalBulletComponentHeader.hlsli"

float4 main(Output input) : SV_TARGET
{
	float u = input.uv.x;
	float v = input.uv.y;
	//�~���S���炱�̓_�܂ł̋���(uv���W��)
	float d = sqrt((u - 0.5) * (u - 0.5) + (v - 0.5) * (v - 0.5));
	//�~�O
	if (d > 0.5)
	{
		discard;
	}
	//�����������ɒ���(�~��->1.0,���S->0.0)
	d /= 0.5;
	return float4(rgb_, alpha_ * d);
}
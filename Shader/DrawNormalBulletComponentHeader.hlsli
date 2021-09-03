//定数バッファ
cbuffer cbuff0:register(b0)
{
	matrix mat_;
	float3 rgb_;
	float alpha_;
}

struct Output {
	float4 svpos:SV_POSITION;
	float2 uv:TEXCOORD;
};
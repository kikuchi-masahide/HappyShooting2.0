//定数バッファ
cbuffer cbuff0:register(b0)
{
	float r_;
	float g_;
	float b_;
	float alpha_;
}

struct Output {
	float4 svpos:SV_POSITION;
	float2 uv:TEXCOORD;
};
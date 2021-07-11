cbuffer cbuff0:register(b0)
{
	matrix exp_;
	matrix trans_ortho_;
	float radius_;
	float alpha_;
}

struct Output {
	float4 svpos_:SV_POSITION;
	float2 uv_:TEXCOORD;
};
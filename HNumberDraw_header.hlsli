Texture2D<float4> tex:register(t0);
SamplerState smp:register(s0);

cbuffer cbuff0:register(b0)
{
	//頂点座標の変換行列
	matrix mat;
	//何番目の数字を表示するか
	vector<unsigned int, 4> index0;
	vector<unsigned int, 4> index1;
}

struct Output {
	float4 svpos_:SV_POSITION;
	float2 uv_:TEXCOORD;
};
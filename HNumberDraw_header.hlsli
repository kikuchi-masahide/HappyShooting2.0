Texture2D<float4> tex:register(t0);
SamplerState smp:register(s0);

cbuffer cbuff0:register(b0)
{
	//���_���W�̕ϊ��s��
	matrix mat;
	//���Ԗڂ̐�����\�����邩
	vector<unsigned int, 4> index0;
	vector<unsigned int, 4> index1;
}

struct Output {
	float4 svpos_:SV_POSITION;
	float2 uv_:TEXCOORD;
};
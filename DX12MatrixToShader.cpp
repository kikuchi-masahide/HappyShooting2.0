#include "DX12MatrixToShader.h"

#include "DX12CommonInclude.h"

DX12MatrixToShader::DX12MatrixToShader()
{
}

DX12MatrixToShader::~DX12MatrixToShader()
{
}

void DX12MatrixToShader::Map(void* map_pointer)
{
	DirectX::XMMATRIX dxmatrix;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			dxmatrix.r[i].m128_f32[j] = data_(j, i);
		}
	}
	DirectX::XMMATRIX* map_vec = (DirectX::XMMATRIX*)map_pointer;
	*map_vec = dxmatrix;
}

SIZE_T DX12MatrixToShader::GetSize() const
{
	return sizeof(DirectX::XMMATRIX);
}

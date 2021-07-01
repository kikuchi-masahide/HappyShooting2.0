#include "DX12VectorToShader.h"

#include "DX12CommonInclude.h"

void DX12Vector2ToShader::Map(void* map_pointer)
{
	DirectX::XMFLOAT2 xmfloat2(data_(0), data_(1));
	auto* matrix_map = static_cast<DirectX::XMFLOAT2*>(map_pointer);
	*matrix_map = xmfloat2;
}

SIZE_T DX12Vector2ToShader::GetSize() const
{
	return sizeof(DirectX::XMFLOAT2);
}

void DX12Vector3ToShader::Map(void* map_pointer)
{
	DirectX::XMFLOAT3 xmfloat3(data_(0), data_(1), data_(2));
	auto* matrix_map = static_cast<DirectX::XMFLOAT3*>(map_pointer);
	*matrix_map = xmfloat3;
}

SIZE_T DX12Vector3ToShader::GetSize() const
{
	return sizeof(DirectX::XMFLOAT3);
}

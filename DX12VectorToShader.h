#pragma once
#include "DX12IShaderTransferable.h"

class DX12Vector2ToShader final
	:public DX12IShaderTransferable
{
public:
	DX12Vector2ToShader() {};
	~DX12Vector2ToShader() {};
	void Map(void* map_pointer) override;
	SIZE_T GetSize() const;
	MatVec::Vector2 data_;
};

class DX12Vector3ToShader final
	:public DX12IShaderTransferable
{
public:
	DX12Vector3ToShader() {};
	~DX12Vector3ToShader() {};
	void Map(void* map_pointer) override;
	SIZE_T GetSize() const;
	MatVec::Vector3 data_;
};
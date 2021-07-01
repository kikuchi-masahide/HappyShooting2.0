#pragma once
#include "DX12IShaderTransferable.h"

class DX12Vector2ToShader final
	:public DX12IShaderTransferable
{
public:
	DX12Vector2ToShader(MatVec::Vector2 data)
		:data_(data)
	{};
	DX12Vector2ToShader()
		:data_(MatVec::Vector2(0,0))
	{};
	~DX12Vector2ToShader() {};
	void Map(void* map_pointer) override;
	SIZE_T GetSize() const;
	MatVec::Vector2 data_;
};

class DX12Vector3ToShader final
	:public DX12IShaderTransferable
{
public:
	DX12Vector3ToShader(MatVec::Vector3 data)
		:data_(data)
	{};
	DX12Vector3ToShader()
		:data_(MatVec::Vector3(0, 0, 0))
	{};
	~DX12Vector3ToShader() {};
	void Map(void* map_pointer) override;
	SIZE_T GetSize() const;
	MatVec::Vector3 data_;
};
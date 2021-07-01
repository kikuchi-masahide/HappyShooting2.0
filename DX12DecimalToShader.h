#pragma once
#include "DX12IShaderTransferable.h"

/// <summary>
/// シェーダに小数を渡すためのクラス
/// double型小数をfloatとして渡す
/// </summary>
class DX12DecimalToShader final
	:public DX12IShaderTransferable
{
public:
	DX12DecimalToShader()
		:data_(0)
	{}
	DX12DecimalToShader(double data)
		:data_(data)
	{}
	~DX12DecimalToShader()
	{}
	void Map(void* map_pointer)
	{
		float* float_pointer = static_cast<float*>(map_pointer);
		*float_pointer = static_cast<float>(data_);
	}
	SIZE_T GetSize()
	{
		return sizeof(float);
	}
	//実データ
	double data_;
};
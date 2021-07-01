#include "stdafx.h"
#include "DX12StructToShader.h"

#include "DX12IShaderTransferable.h"

DX12StructToShader::DX12StructToShader()
	:is_datas_addable_(true)
{
}

DX12StructToShader::~DX12StructToShader()
{
}

void DX12StructToShader::Map(void* map_pointer)
{
	for (unsigned int n = 0; n < datas_.size(); n++)
	{
		//前Mapが呼ばれたときから値が変更されたか
		if (was_changed_[n])
		{
			boost::any_cast<DX12IShaderTransferable>(datas_[n]).Map(map_pointer);
			was_changed_[n] = false;
		}
		//ポインタ演算のためにむりやり
		map_pointer = (char*)map_pointer + data_size_[n];
	}
}

SIZE_T DX12StructToShader::GetSize() const
{
	return whole_size_;
}

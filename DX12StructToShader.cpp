#include "stdafx.h"
#include "DX12StructToShader.h"

DX12StructToShader::DX12StructToShader()
	:is_datas_addable_(true),whole_size_(0)
{
}

DX12StructToShader::~DX12StructToShader()
{
}

void DX12StructToShader::AddData(DX12StructToShader& data)
{
	BOOST_ASSERT(is_datas_addable_);
	AddDataSub(data.GetSize(), InfoType::Struct);
	datas_.push_back(data);
}

void DX12StructToShader::AddData(DX12DecimalToShader& data)
{
	BOOST_ASSERT(is_datas_addable_);
	AddDataSub(data.GetSize(), InfoType::Decimal);
	datas_.push_back(data);
}

void DX12StructToShader::AddData(DX12MatrixToShader& data)
{
	BOOST_ASSERT(is_datas_addable_);
	AddDataSub(data.GetSize(), InfoType::Matrix);
	datas_.push_back(data);
}

void DX12StructToShader::AddData(DX12Vector2ToShader& data)
{
	BOOST_ASSERT(is_datas_addable_);
	AddDataSub(data.GetSize(), InfoType::Vector2);
	datas_.push_back(data);
}

void DX12StructToShader::AddData(DX12Vector3ToShader& data)
{
	BOOST_ASSERT(is_datas_addable_);
	AddDataSub(data.GetSize(), InfoType::Vector3);
	datas_.push_back(data);
}

void DX12StructToShader::Map(void* map_pointer)
{
	for (unsigned int n = 0; n < datas_.size(); n++)
	{
		//前Mapが呼ばれたときから値が変更されたか
		if (was_changed_[n])
		{
			switch (datas_type_[n])
			{
			case InfoType::Struct: {
				auto& data = boost::any_cast<DX12StructToShader&>(datas_[n]);
				data.Map(map_pointer);
				break;
			}
			case InfoType::Decimal: {
				auto& data = boost::any_cast<DX12DecimalToShader&>(datas_[n]);
				data.Map(map_pointer);
				break;
			}
			case InfoType::Matrix: {
				auto& data = boost::any_cast<DX12MatrixToShader&>(datas_[n]);
				data.Map(map_pointer);
				break;
			}
			case InfoType::Vector2: {
				auto& data = boost::any_cast<DX12Vector2ToShader&>(datas_[n]);
				data.Map(map_pointer);
				break;
			}
			case InfoType::Vector3: {
				auto& data = boost::any_cast<DX12Vector3ToShader&>(datas_[n]);
				data.Map(map_pointer);
				break;
			}
			}
		}
		//ポインタ演算のためにむりやり
		map_pointer = (char*)map_pointer + data_size_[n];
	}
}

SIZE_T DX12StructToShader::GetSize() const
{
	return whole_size_;
}

void DX12StructToShader::AddDataSub(SIZE_T size,InfoType type)
{
	was_changed_.push_back(true);
	data_size_.push_back(size);
	whole_size_ += size;
	datas_type_.push_back(type);
}

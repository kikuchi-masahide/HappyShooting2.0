#pragma once

/// <summary>
/// シェーダに渡すデータのためのインターフェース
/// </summary>
class DX12IShaderTransferable {
public:
	DX12IShaderTransferable() {};
	virtual ~DX12IShaderTransferable() {};
	/// <summary>
	/// このポインタに自身のデータをマップする
	/// </summary>
	virtual void Map(void* map_pointer){};
	/// <summary>
	/// このデータがマップされる際の全サイズを取得する
	/// </summary>
	virtual SIZE_T GetSize() const
	{
		return 0;
	};
};
#pragma once
#include "DX12IShaderTransferable.h"

/// <summary>
/// 行列(MatVec::Matrix4x4)をシェーダに送るためのDX12IShaderTrasnferableの実現
/// 自動的に転置して列優先を行優先に直す
/// </summary>
class DX12MatrixToShader final
	:public DX12IShaderTransferable
{
public:
	DX12MatrixToShader();
	~DX12MatrixToShader();
	/// <summary>
	/// 行列をマップする(内部で転置し行優先に直す)
	/// </summary>
	void Map(void* &map_pointer) override;
	SIZE_T GetSize() const override;
	//実データ
	MatVec::Matrix4x4 data_;
};
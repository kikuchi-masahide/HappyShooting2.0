#pragma once
#include "DX12IShaderTransferable.h"

/// <summary>
/// �s��(MatVec::Matrix4x4)���V�F�[�_�ɑ��邽�߂�DX12IShaderTrasnferable�̎���
/// �����I�ɓ]�u���ė�D����s�D��ɒ���
/// </summary>
class DX12MatrixToShader final
	:public DX12IShaderTransferable
{
public:
	DX12MatrixToShader();
	~DX12MatrixToShader();
	/// <summary>
	/// �s����}�b�v����(�����œ]�u���s�D��ɒ���)
	/// </summary>
	void Map(void* &map_pointer) override;
	SIZE_T GetSize() const override;
	//���f�[�^
	MatVec::Matrix4x4 data_;
};
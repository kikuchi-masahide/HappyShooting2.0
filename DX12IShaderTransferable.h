#pragma once

/// <summary>
/// �V�F�[�_�ɓn���f�[�^�̂��߂̃C���^�[�t�F�[�X
/// </summary>
class DX12IShaderTransferable {
public:
	DX12IShaderTransferable() {};
	virtual ~DX12IShaderTransferable() {};
	/// <summary>
	/// ���̃|�C���^�Ɏ��g�̃f�[�^���}�b�v����
	/// </summary>
	virtual void Map(void* map_pointer){};
	/// <summary>
	/// ���̃f�[�^���}�b�v�����ۂ̑S�T�C�Y���擾����
	/// </summary>
	virtual SIZE_T GetSize() const
	{
		return 0;
	};
};
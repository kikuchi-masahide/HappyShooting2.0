#pragma once

/// <summary>
/// 1��DX12DescriptorRange��1��DescriptorHeap�ƑΉ����C
/// �e�r���[���ǂ̂悤�ɃV�F�[�_���W�X�^�ƑΉ����邩�w�肷��D
/// see:https://sites.google.com/site/monshonosuana/directxno-hanashi-1/directx-145
/// </summary>
struct DX12DescriptorRange {
public:
	/// <summary>
	/// �ߑ�����f�B�X�N���v�^�̐�
	/// </summary>
	unsigned int mNumDescriptors;
	/// <summary>
	/// �ߑ�����f�B�X�N���v�^�̎��
	/// </summary>
	DX12Config::DescriptorRangeType mType;
	/// <summary>
	/// �V�F�[�_���W�X�^�̉��Ԗڂ����L���邩
	/// (�Ⴆ��mBaseShaderRegister = 2,mNumDescriptors = 4,mType = CBV�Ȃ�΁C
	/// ���̃f�B�X�N���v�^�����W��b2����b5���L����)
	/// </summary>
	unsigned int mBaseShaderRegister;
	/// <summary>
	/// �f�B�X�N���v�^�q�[�v�̉��Ԗڂ����L���邩
	/// (�Ⴆ��mBaseHeapRegister = 2,mNumDescriptors = 4�Ȃ�΁C
	/// �f�B�X�N���v�^�q�[�v��2����5�Ԗڂ��L����)
	/// </summary>
	unsigned int mBaseHeapRegister;
	DX12DescriptorRange(unsigned int _num, DX12Config::DescriptorRangeType _type, unsigned int _shaderreg, unsigned int _heapreg)
		:mNumDescriptors(_num), mType(_type), mBaseShaderRegister(_shaderreg),mBaseHeapRegister(_heapreg)
	{}
};

/// <summary>
/// �����̃f�B�X�N���v�^�����W���܂Ƃ߂�\����
/// see:https://sites.google.com/site/monshonosuana/directxno-hanashi-1/directx-145
/// </summary>
struct DX12RootParameter {
public:
	DX12Config::RootParameterShaderVisibility mShaderVisibility;
	/// <summary>
	/// �����Ă���f�B�X�N���v�^�����W��vector
	/// </summary>
	std::vector<DX12DescriptorRange> mDescRanges;
};
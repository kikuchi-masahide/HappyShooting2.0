#pragma once

/// <summary>
/// 1��DX12DescriptorRange�́C1��DescriptorHeap�̎���
/// ����̘A�������f�B�X�N���v�^���V�F�[�_���W�X�^�Ƀo�C���h����
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
	DX12DescriptorRange(unsigned int _num, DX12Config::DescriptorRangeType _type, unsigned int _reg)
		:mNumDescriptors(_num), mType(_type), mBaseShaderRegister(_reg)
	{}
};

/// <summary>
/// �����̃f�B�X�N���v�^�����W���܂Ƃ߂�\����
/// (�{���̓f�B�X�N���v�^�����W�̓f�B�X�N���v�^�e�[�u���ɂ��܂Ƃ߂��C�����̃e�[�u�������[�g�p�����^�ɂ��܂Ƃ߂��邪�C
/// �����ł͊ȒP�̂��ߑS�f�B�X�N���v�^�����W��1�̃e�[�u���ɂ܂Ƃ߁C�����1�̃��[�g�p�����^�����悤�ɂ���)
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
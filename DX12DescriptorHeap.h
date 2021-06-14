#pragma once

#include "DX12CommonInclude.h"

#include "DX12ConfigEnums.h"

class DX12Device;
class DX12Resource;
class DX12CmdList;

class DX12DescriptorHeap final :public boost::noncopyable {
public:
	//�R���X�g���N�^
	DX12DescriptorHeap(DX12Config::DescriptorHeapType _type, DX12Config::DescriptorHeapShaderVisibility _vis, unsigned int _num, ComPtr<ID3D12Device> _device);
	~DX12DescriptorHeap();
	/// <summary>
	/// _n�Ԗڂ�CPU�n���h���擾
	/// </summary>
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(unsigned int _n);
	//�R�}���h���X�g�ɑ΂���f�B�X�N���v�^�q�[�v�̎w��
	void SetDescriptorHeap(ComPtr<ID3D12GraphicsCommandList> _cmdlist);
	const DX12Config::DescriptorHeapType GetDescriptorHeapType();
	const DX12Config::DescriptorHeapShaderVisibility GetShaderVisibility();
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(unsigned int _n);
private:
	//���L�f�B�X�N���v�^�̐�
	const unsigned int mNum;
	const DX12Config::DescriptorHeapType mType;
	const DX12Config::DescriptorHeapShaderVisibility mShaderVisibility;
	ComPtr<ID3D12DescriptorHeap> mDescHeap;
	//1�f�B�X�N���v�^������̃f�B�X�N���v�^�n���h���n���h��
	SIZE_T mDescriptorHandleSize;
	//�f�B�X�N���v�^�q�[�v�������ŗp����\����(���ʂ���ݒ�͂���ɐݒ肵�Ă���)
	static D3D12_DESCRIPTOR_HEAP_DESC mHeapDescStr;
	//DX12Config::DescriptorHeapType�̊e�萔�����������ǂ̒萔�ɑΉ����邩
	static D3D12_DESCRIPTOR_HEAP_TYPE mDescriptorHeapTypeCorrespond[(unsigned char)DX12Config::DescriptorHeapType::size];
	//DX12Config::ShaderVisibility�̊e�萔�����������ǂ̒萔�ɑΉ����邩
	static D3D12_DESCRIPTOR_HEAP_FLAGS mShaderVisibilityCorrespond[(unsigned char)DX12Config::DescriptorHeapShaderVisibility::size];
};
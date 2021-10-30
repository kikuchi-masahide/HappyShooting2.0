#pragma once
#include "DX12CommonInclude.h"

class DX12Resource;
class DX12DescriptorHeap;

class DX12SwapChain {
public:
	DX12SwapChain(ComPtr<IDXGIFactory6> _factory, ComPtr<ID3D12CommandQueue> _cmdqueue, ComPtr<ID3D12Device> _device, HWND _hwnd, UINT _width, UINT _height);
	/// <summary>
	/// �t���b�v
	/// </summary>
	void Filp();
	UINT GetCurrentBackBufferIndex();
	void ClearRenderTarget(ComPtr<ID3D12GraphicsCommandList> _list, float _r, float _g, float _b);
	/// <summary>
	/// _list����OMSetRenderTargets���s��(���\�[�X�o���A������)
	/// </summary>
	void OpenRenderTargets(ComPtr<ID3D12GraphicsCommandList> _list);
	/// <summary>
	/// ���\�[�X�o���A��ݒ肵�����_�[�^�[�Q�b�g�����
	/// </summary>
	void CloseRenderTarget(ComPtr<ID3D12GraphicsCommandList> _list);
private:
	ComPtr<IDXGISwapChain4> mSwapChain;
	//���\�[�X(mBackBuffers[BackBuffer�����ڂ�][id])
	boost::shared_ptr<DX12Resource> mBuffers[2];
	//�e�X���b�v�`�F�[���ɑ΂���r���[�����f�B�X�N���v�^�q�[�v
	//(1�̃f�B�X�N���v�^�q�[�v��1�̃X���b�v�`�F�[�����Ǘ�����Ɗm�񂷂�)
	boost::shared_ptr<DX12DescriptorHeap> mDescHeap;
	//�X���b�v�`�F�[���̐ݒ�̂������ʂ������
	static DXGI_SWAP_CHAIN_DESC1 mBaseDesc;
};
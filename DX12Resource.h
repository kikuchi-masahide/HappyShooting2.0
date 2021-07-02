#pragma once

#include "DX12CommonInclude.h"
#include "DX12ConfigEnums.h"

class DX12Device;
class DX12CmdList;
class DX12DescriptorHeap;

class DX12Resource final :public boost::noncopyable {
public:
	DX12Resource(ComPtr<ID3D12Device> _device, DX12Config::ResourceHeapType _heaptype,UINT64 _width,UINT _height, LPCWSTR _name);
	DX12Resource(ComPtr<ID3D12Device> _device, DirectX::TexMetadata& _metadata, LPCWSTR _name);
	DX12Resource(ComPtr<IDXGISwapChain4> _swapchain,UINT _n);
	DX12Resource(ComPtr<ID3D12Device> _device, UINT64 _width, UINT64 _height, float _r, float _g, float _b, float _alpha, LPCWSTR _name );
	DX12Resource(ComPtr<ID3D12Device> _device, DX12Config::ResourceHeapType _heaptype, UINT64 _constbytesize, LPCWSTR _name);
	void* Map();
	void Unmap();
	//�o�b�t�@�̉��z�A�h���X
	D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress();
	//�R�}���h���X�g�ɒ��_�o�b�t�@���Z�b�g
	void SetVertexBuffers(ComPtr<ID3D12GraphicsCommandList> _list,unsigned int _slotid, SIZE_T _allsize,
		SIZE_T _sizepervertex);
	//�R�}���h���X�g�ɃC���f�b�N�X�o�b�t�@���Z�b�g
	void SetIndexBuffers(ComPtr<ID3D12GraphicsCommandList> _list, unsigned int _vertnum);
	ComPtr<ID3D12Resource> mResource;
	//���\�[�X�o���A�̃Z�b�g
	void SetResourceBarrier(ComPtr<ID3D12GraphicsCommandList> _list, DX12Config::ResourceBarrierState _before, DX12Config::ResourceBarrierState _after);
	/// <summary>
	/// �w��f�B�X�N���v�^�q�[�v��ɂ��̃��\�[�X�̃����_�[�^�[�Q�b�g�r���[�����
	/// </summary>
	/// <param name="_n">�f�B�X�N���v�^�q�[�v�̉��ԖڂɃr���[����邩</param>
	void CreateRenderTargetView(ComPtr<ID3D12Device> _device, boost::shared_ptr<DX12DescriptorHeap> _descheap, int _n);
	/// <summary>
	/// �w��f�B�X�N���v�^�q�[�v��ɂ��̃��\�[�X�̃����_�[�^�[�Q�b�g�r���[�����
	/// </summary>
	/// <param name="_n">�f�B�X�N���v�^�q�[�v�̉��ԖڂɃr���[����邩</param>
	void CreateShaderResourceView(ComPtr<ID3D12Device> _device, boost::shared_ptr<DX12DescriptorHeap> _descheap, int _n);
private:
	static D3D12_HEAP_TYPE mResourceHeapTypeCorrespond[(unsigned char)DX12Config::ResourceHeapType::size];
	static D3D12_RESOURCE_STATES mResourceStateCorrespond[(unsigned char)DX12Config::ResourceBarrierState::size];
};
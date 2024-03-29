#include "DX12DescriptorHeap.h"
#include "DX12Resource.h"
#include "DX12Pimple.h"

DX12DescriptorHeap::DX12DescriptorHeap(DX12Config::DescriptorHeapType _type, DX12Config::DescriptorHeapShaderVisibility _vis, unsigned int _num, ComPtr<ID3D12Device> _device, LPCWSTR _name)
	:mNum(_num), mType(_type), mShaderVisibility(_vis)
{
	//mHeapDescStrの対応箇所変更
	mHeapDescStr.Type = mDescriptorHeapTypeCorrespond[(unsigned char)_type];
	mHeapDescStr.Flags = mShaderVisibilityCorrespond[(unsigned char)_vis];
	mHeapDescStr.NumDescriptors = _num;
	mHeapDescStr.NodeMask = 0;
	auto res = _device->CreateDescriptorHeap(&mHeapDescStr, IID_PPV_ARGS(mDescHeap.ReleaseAndGetAddressOf()));
	BOOST_ASSERT_MSG(SUCCEEDED(res), "failed in creating descriptorheap");
	mDescriptorHandleSize = _device->GetDescriptorHandleIncrementSize(mDescriptorHeapTypeCorrespond[(unsigned char)_type]);
#ifdef _DEBUG
	mDescHeap->SetName(_name);
#endif
}

DX12DescriptorHeap::~DX12DescriptorHeap()
{
}

D3D12_CPU_DESCRIPTOR_HANDLE DX12DescriptorHeap::GetCPUDescriptorHandle(unsigned int _n)
{
	auto handle = mDescHeap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += _n * mDescriptorHandleSize;
	return handle;
}

const DX12Config::DescriptorHeapType DX12DescriptorHeap::GetDescriptorHeapType()
{
	return mType;
}

const DX12Config::DescriptorHeapShaderVisibility DX12DescriptorHeap::GetShaderVisibility()
{
	return mShaderVisibility;
}

D3D12_GPU_DESCRIPTOR_HANDLE DX12DescriptorHeap::GetGPUDescriptorHandle(unsigned int _n)
{
	auto handle = mDescHeap->GetGPUDescriptorHandleForHeapStart();
	handle.ptr += _n * mDescriptorHandleSize;
	return handle;
}

boost::shared_ptr<DX12DescriptorHeap> DX12Pimple::CreateDescriptorHeap(DX12Config::DescriptorHeapType _type, DX12Config::DescriptorHeapShaderVisibility _vis, unsigned int _num, LPCWSTR _name)
{
	return boost::shared_ptr<DX12DescriptorHeap>(
		DBG_NEW DX12DescriptorHeap(_type, _vis, _num, mDevice, _name)
		);
}

D3D12_DESCRIPTOR_HEAP_DESC DX12DescriptorHeap::mHeapDescStr = {
	D3D12_DESCRIPTOR_HEAP_TYPE_RTV,0,D3D12_DESCRIPTOR_HEAP_FLAG_NONE,0
};

D3D12_DESCRIPTOR_HEAP_TYPE DX12DescriptorHeap::mDescriptorHeapTypeCorrespond[] = {
	/*RTV*/D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
	/*CBV,SRV,UAV*/D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
	/*DSV*/D3D12_DESCRIPTOR_HEAP_TYPE_DSV
};

D3D12_DESCRIPTOR_HEAP_FLAGS DX12DescriptorHeap::mShaderVisibilityCorrespond[] = {
	D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
	D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE
};

void DX12Pimple::SetDescriptorHeap(boost::shared_ptr<DX12DescriptorHeap> _descHeap)
{
	if (current_descheap_ == _descHeap)return;
	ID3D12DescriptorHeap* arr[1] = {
		_descHeap->mDescHeap.Get()
	};
	mCmdList->SetDescriptorHeaps(1,arr);
	current_descheap_ = _descHeap;
}

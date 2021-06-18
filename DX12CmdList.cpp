#include "DX12Resource.h"
#include "DX12DescriptorHeap.h"
#include "DX12Pimple.h"
#include "DX12SwapChain.h"

D3D12_PRIMITIVE_TOPOLOGY PrimitiveTopologyTypeCorrespond[(unsigned char)DX12Config::PrimitiveTopology::size] = {
	D3D_PRIMITIVE_TOPOLOGY_POINTLIST,
	D3D_PRIMITIVE_TOPOLOGY_LINELIST,
	D3D_PRIMITIVE_TOPOLOGY_LINESTRIP,
	D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
	D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
};

void DX12Pimple::SetPrimitiveTopology(DX12Config::PrimitiveTopology _prim)
{
	mCmdList->IASetPrimitiveTopology(PrimitiveTopologyTypeCorrespond[(unsigned char)_prim]);
}

void DX12Pimple::DrawIndexedInstanced(UINT _indexnumperinst, UINT _instnum, UINT _indoffset, UINT _vdataoffset, UINT _instoffset)
{
	mCmdList->DrawIndexedInstanced(_indexnumperinst, _instnum, _indoffset, _vdataoffset, _instoffset);
}

void DX12Pimple::SetViewports(UINT _widthpx, UINT _heightpx, int _topleftx, int _toplefty,
	float _maxdepth, float _mindepth)
{
	D3D12_VIEWPORT viewport = {};
	viewport.Width = _widthpx;
	viewport.Height = _heightpx;
	viewport.TopLeftX = _topleftx;
	viewport.TopLeftY = _toplefty;
	viewport.MaxDepth = _maxdepth;
	viewport.MinDepth = _mindepth;
	mCmdList->RSSetViewports(1, &viewport);
}

void DX12Pimple::SetScissorrect(float _top, float _bottom, float _left, float _right)
{
	D3D12_RECT scissorrect = {};
	scissorrect.top = _top;
	scissorrect.bottom = _bottom;
	scissorrect.left = _left;
	scissorrect.right = _right;
	mCmdList->RSSetScissorRects(1, &scissorrect);
}

void DX12Pimple::SetGraphicsRootDescriptorTable(unsigned int _rootParamIndex, boost::shared_ptr<DX12DescriptorHeap> _descHeap, unsigned int _descHeapIndex)
{
	mCmdList->SetGraphicsRootDescriptorTable(_rootParamIndex, _descHeap->GetGPUDescriptorHandle(_descHeapIndex));
}

void DX12Pimple::SetResourceBarrier(boost::shared_ptr<DX12Resource> _resource, DX12Config::ResourceBarrierState _before, DX12Config::ResourceBarrierState _after)
{
	_resource->SetResourceBarrier(mCmdList, _before, _after);
}

void DX12Pimple::DrawInstanced(UINT vertex_count_per_instance, UINT instance_count, UINT start_vertex_location, UINT start_instance_location)
{
	mCmdList->DrawInstanced(vertex_count_per_instance, instance_count, start_vertex_location, start_instance_location);
}

boost::shared_ptr<DX12SwapChain> DX12Pimple::CreateSwapChain(HWND _hwnd, UINT _width, UINT _height)
{
	return boost::shared_ptr<DX12SwapChain>(new DX12SwapChain(mFactory, mCmdQueue, mDevice, _hwnd, _width, _height));
}

void DX12Pimple::FlipSwapChain(boost::shared_ptr<DX12SwapChain> _swapchain)
{
	_swapchain->Filp();
}

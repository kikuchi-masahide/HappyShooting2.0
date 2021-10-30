#pragma once
#include "DX12CommonInclude.h"
#include "DX12VertexLayoutUnit.h"

class DX12DescriptorHeap;
class DX12GraphicsPipeline;
class DX12Resource;
struct DX12DescriptorRange;
struct DX12RootParameter;
class DX12RootSignature;
class DX12ShaderObject;
class DX12SwapChain;

class DX12Pimple final:public boost::noncopyable {
private:
	ComPtr<ID3D12CommandAllocator> mCmdAllocator;
	ComPtr<ID3D12GraphicsCommandList> mCmdList;
	ComPtr<ID3D12CommandQueue> mCmdQueue;
	ComPtr<ID3D12Device> mDevice;
	ComPtr<ID3D12InfoQueue> mInfoQueue;   //�����_�[�^�[�Q�b�g�N���A�F�Ⴂ�̌x���}���̂���
	ComPtr<IDXGIFactory6> mFactory;
	void FenceWaitingInProcessCommands();
	boost::shared_ptr<DX12Resource> CreateTextureUploadBuffer(unsigned int _rowpitch, unsigned int _height, LPCWSTR _name);
	//�A�����ē������̂��Z�b�g���Ȃ��悤�ɕۑ����Ă���(tick�؂�ւ�����������x�ݒ肵�Ȃ��Ƃ����Ȃ�)
	boost::shared_ptr<DX12GraphicsPipeline> current_pipeline_;
	boost::shared_ptr<DX12RootSignature> current_rootsign_;
	boost::shared_ptr<DX12DescriptorHeap> current_descheap_;
	DX12Config::PrimitiveTopology current_primitivetop_;
	boost::shared_ptr<DX12Resource> current_vertexbuffer_;
	boost::shared_ptr<DX12Resource> current_indexbuffer_;
	//�Scurrent_������������
	void ClearCurrentConfig();
public:
	DX12Pimple();
	void Initialize();
	void CleanUp();
	~DX12Pimple();
	void ProcessCommands();
	void ResetCmdAllocator();
	void ExecuteCmdLists();
	boost::shared_ptr<DX12Resource> CreateVertexBuffer(UINT64 _width, LPCWSTR _name);
	void* Map(boost::shared_ptr<DX12Resource> _resource);
	void Unmap(boost::shared_ptr<DX12Resource> _resource);
	boost::shared_ptr<DX12ShaderObject> LoadShader(LPCWSTR _filename, DX12Config::ShaderType _shaderType);
	boost::shared_ptr<DX12GraphicsPipeline> CreateGraphicsPipeline(
		boost::shared_ptr<DX12ShaderObject> _vertexShader,
		boost::shared_ptr<DX12ShaderObject> _pixelShader, DX12VertexLayout& _vertexLayout,
		DX12Config::PrimitiveTopologyType _primitive, UINT _numrt,
		boost::shared_ptr<DX12RootSignature> _rootsignature, LPCWSTR _name);
	boost::shared_ptr<DX12RootSignature> CreateRootSignature(DX12RootParameter& _descheap_rootparam, bool _hasSampler);
	void SetGraphicsPipeline(boost::shared_ptr<DX12GraphicsPipeline> _pipeline);
	void SetRootSignature(boost::shared_ptr<DX12RootSignature> _root);
	void SetPrimitiveTopology(DX12Config::PrimitiveTopology _prim);
	void SetVertexBuffers(boost::shared_ptr<DX12Resource> _resource, unsigned int _slotid,
		SIZE_T _allsize, SIZE_T _sizepervertex);
	void DrawIndexedInstanced(UINT _indexnumperinst, UINT _instnum, UINT _indoffset,
		UINT _vdataoffset, UINT _instoffset);
	void SetViewports(UINT _widthpx, UINT _heightpx, int _topleftx, int _toplefty,
		float _maxdepth, float _mindepth);
	void SetScissorrect(float _top, float _bottom, float _left, float _right);
	void SetIndexBuffers(boost::shared_ptr<DX12Resource> _resource, unsigned int _vertnum);
	boost::shared_ptr<DX12Resource> CreateIndexBuffer(unsigned int _vertnum, LPCWSTR _name);
	struct TextureInfo
	{
	public:
		boost::shared_ptr<DX12Resource> texture_resource_;
		char format_;
	};
	TextureInfo LoadTexture(const wchar_t* _filename, LPCWSTR _buffername);
	void SetDescriptorHeap(boost::shared_ptr<DX12DescriptorHeap> _descHeap);
	void SetGraphicsRootDescriptorTable(unsigned int _rootParamIndex, boost::shared_ptr<DX12DescriptorHeap> _descHeap, unsigned int _descHeapIndex);
	void SetResourceBarrier(boost::shared_ptr<DX12Resource> _resource, DX12Config::ResourceBarrierState _before, DX12Config::ResourceBarrierState _after);
	boost::shared_ptr<DX12SwapChain> CreateSwapChain(HWND _hwnd, UINT _width, UINT _height);
	void FlipSwapChain(boost::shared_ptr<DX12SwapChain> _swapchain);
	void OpenRenderTarget(boost::shared_ptr<DX12SwapChain> _swapchain);
	void CloseRenderTarget(boost::shared_ptr<DX12SwapChain> _swapchain);
	void ClearRenderTarget(boost::shared_ptr<DX12SwapChain> _swapchain, float _r, float _g, float _b);
	void OpenRenderTarget(boost::shared_ptr<DX12DescriptorHeap> _heap, unsigned int _id);
	void ClearRenderTarget(boost::shared_ptr<DX12DescriptorHeap> _heap, unsigned int _id, float _r, float _g, float _b,float _alpha);
	boost::shared_ptr<DX12DescriptorHeap> CreateDescriptorHeap(DX12Config::DescriptorHeapType _type, DX12Config::DescriptorHeapShaderVisibility _vis, unsigned int _num, LPCWSTR _name);
	boost::shared_ptr<DX12Resource> CreateClearTexture(UINT64 _width, UINT64 _height, float _r, float _g, float _b, float _alpha, LPCWSTR _name);
	void CreateRenderTargetView(boost::shared_ptr<DX12Resource> _resource, boost::shared_ptr<DX12DescriptorHeap> _descheap, int _n);
	void CreateShaderResourceView(boost::shared_ptr<DX12Resource> _resource, boost::shared_ptr<DX12DescriptorHeap> _descheap, int _n, unsigned char _format);
	boost::shared_ptr<DX12Resource> CreateConstBuffer(DX12Config::ResourceHeapType _resheaptype, UINT64 _bytesize, LPCWSTR _name);
	void CreateConstBufferView(boost::shared_ptr<DX12Resource> _resource, boost::shared_ptr<DX12DescriptorHeap> _descheap, int _n);
	void DrawInstanced(UINT vertex_count_per_instance, UINT instance_count, UINT start_vertex_location, UINT start_instance_location);
};
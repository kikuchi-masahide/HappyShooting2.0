#include "DX12Pimple.h"
#include "DX12DescriptorHeap.h"
#include "DX12GraphicsPipeline.h"
#include "DX12Resource.h"
#include "DX12RootParameter.h"
#include "DX12RootSignature.h"
#include "DX12ShaderObject.h"
#include "DX12VertexLayoutUnit.h"
#include "Log.h"
#include <DirectXMath.h>

void DX12Pimple::ClearCurrentConfig()
{
	current_pipeline_ = nullptr;
	current_rootsign_ = nullptr;
	current_descheap_ = nullptr;
	current_primitivetop_ = DX12Config::PrimitiveTopology::size;
	current_vertexbuffer_ = nullptr;
	current_indexbuffer_ = nullptr;
}

DX12Pimple::DX12Pimple()
{}

void DX12Pimple::Initialize() {
	//�f�o�b�O���C���̗L����
//#ifdef _DEBUG
	try {
		{
			ComPtr<ID3D12Debug1> debugLayer;
			if (FAILED(
				D3D12GetDebugInterface(
					IID_PPV_ARGS(debugLayer.ReleaseAndGetAddressOf())
				)
			))
			{
				Log::OutputCritical("ID3D12Debug Initialization failed");
				throw 0;
			}
			debugLayer->EnableDebugLayer();
			debugLayer->SetEnableGPUBasedValidation(true);
		}
	}
	catch (...)
	{
		throw;
	}
//#endif
	try {
		//�f�o�C�X������
		{
			D3D_FEATURE_LEVEL levels[] = {
				D3D_FEATURE_LEVEL_12_1,
				D3D_FEATURE_LEVEL_12_0,
				D3D_FEATURE_LEVEL_11_1,
				D3D_FEATURE_LEVEL_11_0
			};
			auto succeed_level = D3D_FEATURE_LEVEL_10_1;
			for (auto lv : levels)
			{
				if (SUCCEEDED(
					D3D12CreateDevice(
						nullptr, lv, IID_PPV_ARGS(mDevice.ReleaseAndGetAddressOf())
					)
				))
				{
					succeed_level = lv;
					break;
				}
			}
			if (succeed_level == D3D_FEATURE_LEVEL_10_1)
			{
				Log::OutputCritical("D3D12CreateDevice() failed\n");
				throw 0;
			}
		}
		//�t�@�N�g��������
		{
#ifdef _DEBUG
			auto result = CreateDXGIFactory2(
				DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(mFactory.ReleaseAndGetAddressOf()));
			if (FAILED(result))
			{
				Log::OutputCritical("IDXGIFactory6 Initialization failed");
				throw 0;
			}
#else
			if (FAILED(
				CreateDXGIFactory1(
					IID_PPV_ARGS(mFactory.ReleaseAndGetAddressOf())
				)
			))
			{
				Log::OutputCritical("IDXGIFactory6 Initialization failed");
				throw 0;
			}
#endif
		}
		//�R�}���h�A���P�[�^������
		{
			if (FAILED(
				mDevice->CreateCommandAllocator(
					D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(mCmdAllocator.ReleaseAndGetAddressOf())
				)
			))
			{
				Log::OutputCritical("ID3D12CommandAllocator Initialization failed");
				throw 0;
			}
		}
		//�R�}���h���X�g������
		{
			if (FAILED(
				mDevice->CreateCommandList(
					0, D3D12_COMMAND_LIST_TYPE_DIRECT, mCmdAllocator.Get(), nullptr,
					IID_PPV_ARGS(mCmdList.ReleaseAndGetAddressOf())
				)
			))
			{
				Log::OutputCritical("ID3D12GraphicsCommandList Initialization failed");
				throw 0;
			}
			mCmdList->SetName(L"CommandList0");
		}
		//�R�}���h�L���[������
		{
			D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
			cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			cmdQueueDesc.NodeMask = 0;
			cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
			cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
			if (FAILED(
				mDevice->CreateCommandQueue(
					&cmdQueueDesc, IID_PPV_ARGS(mCmdQueue.ReleaseAndGetAddressOf())
				)
			))
			{
				Log::OutputCritical("ID3D12CommandQueue Initialization failed");
				throw 0;
			}
		}
		//�e�N�X�`�����[�h�p��COM������
		{
			if (FAILED(CoInitializeEx(0, COINIT_MULTITHREADED)))
			{
				throw 0;
			}
		}
		ComPtr<ID3D12DeviceRemovedExtendedDataSettings1> dred_settings;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(dred_settings.ReleaseAndGetAddressOf()))))
		{
			dred_settings->SetAutoBreadcrumbsEnablement(D3D12_DRED_ENABLEMENT_FORCED_ON);
			dred_settings->SetBreadcrumbContextEnablement(D3D12_DRED_ENABLEMENT_FORCED_ON);
			dred_settings->SetPageFaultEnablement(D3D12_DRED_ENABLEMENT_FORCED_ON);
		}
		mDevice.As(&mInfoQueue);
		D3D12_MESSAGE_ID deny_ids[] = {
			D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE
		};
		D3D12_MESSAGE_SEVERITY severities[] = {
			D3D12_MESSAGE_SEVERITY_INFO
		};
		D3D12_INFO_QUEUE_FILTER filter{};
		filter.DenyList.NumIDs = _countof(deny_ids);
		filter.DenyList.pIDList = deny_ids;
		filter.DenyList.NumSeverities = _countof(severities);
		filter.DenyList.pSeverityList = severities;
		mInfoQueue->PushStorageFilter(&filter);
		//D3D12�̃G���[���Ɏ~�߂�悤�ɂ���
		mInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, TRUE);
	}
	catch (...)
	{
		throw;
	}
	ClearCurrentConfig();
}

void DX12Pimple::CleanUp() {
	//HACK:�Ō�ɂ��������ǃ`�F�b�N�𓥂܂Ȃ��ƁC�E�B���h�E�폜�ȊO�Ń��[�v�𔲂��悤�Ƃ�����
	//�uOBJECT_DELETED_WHILE_STILL_IN_USE�v�œ{����̂�
	ProcessCommands();
}

DX12Pimple::~DX12Pimple()
{
	//ComPtr<ID3D12DebugDevice> mDebugDevice;
	//mDevice->QueryInterface(mDebugDevice.GetAddressOf());
	//mDebugDevice->ReportLiveDeviceObjects(D3D12_RLDO_DETAIL);
}

void DX12Pimple::ProcessCommands()
{
	//���߂̃N���[�Y
	mCmdList->Close();
	//�R�}���h���X�g���s
	ExecuteCmdLists();
	//Reset�̑O�Ƀt�F���X���͂���
	FenceWaitingInProcessCommands();
	//�L���[���N���A
	mCmdAllocator->Reset();
	//�ĂуR�}���h���X�g�����߂鏀��
	ResetCmdAllocator();
	ClearCurrentConfig();
}

void DX12Pimple::ResetCmdAllocator()
{
	mCmdList->Reset(mCmdAllocator.Get(), nullptr);
}

void DX12Pimple::ExecuteCmdLists()
{
	ID3D12CommandList* cmdlists[] = { mCmdList.Get() };
	mCmdQueue->ExecuteCommandLists(1, cmdlists);
}

void DX12Pimple::FenceWaitingInProcessCommands()
{
	//HACK:CPU��GPU�����ɓ������ĐQ�����Ȃ��Ă������悤�ɂ���ɂ́C�R�}���h���X�g�𕡐������Ƃ��K�v?
	//https://shobomaru.wordpress.com/2015/07/12/d3d12-fence/
	static ComPtr<ID3D12Fence> fence = nullptr;
	static UINT64 fenceVal = 0;
	static auto fence_event = CreateEvent(NULL, FALSE, FALSE, NULL);
	//�����s���̂ݏ�����
	if (!fence) {
		mDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.ReleaseAndGetAddressOf()));
	}
	fence->SetEventOnCompletion(++fenceVal, fence_event);
	mCmdQueue->Signal(fence.Get(), fenceVal);
	WaitForSingleObject(fence_event, INFINITE);
}

boost::shared_ptr<DX12Resource> DX12Pimple::CreateTextureUploadBuffer(unsigned int _rowpitch,unsigned int _height, LPCWSTR _name)
{
	auto aligned = _rowpitch + D3D12_TEXTURE_DATA_PITCH_ALIGNMENT - _rowpitch % D3D12_TEXTURE_DATA_PITCH_ALIGNMENT;
	return boost::shared_ptr<DX12Resource>(DBG_NEW DX12Resource(
		mDevice,DX12Config::ResourceHeapType::UPLOAD,aligned*_height,1,_name
	));
}

DX12Pimple::TextureInfo DX12Pimple::LoadTexture(const wchar_t* _filename, LPCWSTR _buffername)
{
	//WIC�e�N�X�`���̃��[�h
	DirectX::TexMetadata metadata = {};
	DirectX::ScratchImage scratchImg = {};
	auto result = LoadFromWICFile(_filename, DirectX::WIC_FLAGS::WIC_FLAGS_NONE, &metadata, scratchImg);
	if (FAILED(result))throw 0;
	auto img = scratchImg.GetImage(0, 0, 0);//���f�[�^���o

	auto alignmentedSize = img->rowPitch + D3D12_TEXTURE_DATA_PITCH_ALIGNMENT - img->rowPitch % D3D12_TEXTURE_DATA_PITCH_ALIGNMENT;
	auto uploadResource = CreateTextureUploadBuffer(img->rowPitch,img->height, _buffername);


	//�ǂݎ��p�o�b�t�@
	auto texResource = boost::shared_ptr<DX12Resource>(
		DBG_NEW DX12Resource(mDevice, metadata, _buffername)
		);

	//�]���p���\�[�X�Ƀ}�b�v
	uint8_t* mapforImg = (uint8_t*)uploadResource->Map();
	auto srcAddress = img->pixels;
	auto rowPitch = alignmentedSize;
	for (int y = 0; y < img->height; ++y) {
		std::copy_n(srcAddress,
			rowPitch, 
			mapforImg);//�R�s�[
		//1�s���Ƃ̒�������킹�Ă��
		srcAddress += img->rowPitch;
		mapforImg += rowPitch;
	}

	uploadResource->Unmap();//�A���}�b�v

	auto texResourcerow = texResource->mResource.Get();
	auto uploadResourcerow = uploadResource->mResource.Get();


	//upload����tex�ւ̃R�s�[
	D3D12_TEXTURE_COPY_LOCATION src = {}, dst = {};
	dst.pResource = texResourcerow;
	dst.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
	dst.SubresourceIndex = 0;
	src.pResource = uploadResourcerow;//���ԃo�b�t�@
	src.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;//�t�b�g�v�����g�w��
	D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint = {};
	UINT nrow;
	UINT64 rowsize, size;
	auto desc = texResourcerow->GetDesc();
	mDevice->GetCopyableFootprints(&desc, 0, 1, 0, &footprint, &nrow, &rowsize, &size);
	src.PlacedFootprint = footprint;
	src.PlacedFootprint.Offset = 0;
	src.PlacedFootprint.Footprint.Width = metadata.width;
	src.PlacedFootprint.Footprint.Height = metadata.height;
	src.PlacedFootprint.Footprint.Depth = metadata.depth;
	src.PlacedFootprint.Footprint.RowPitch = alignmentedSize;
	src.PlacedFootprint.Footprint.Format = img->format;
	mCmdList->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);

	//���\�[�X�o���A
	SetResourceBarrier(texResource, DX12Config::ResourceBarrierState::COPY_DEST, DX12Config::ResourceBarrierState::PIXEL_SHADER_RESOURCE);

	mCmdList->Close();
	//�R�}���h���X�g�̎��s
	ID3D12CommandList* cmdlists[] = { mCmdList.Get() };
	mCmdQueue->ExecuteCommandLists(1, cmdlists);
	FenceWaitingInProcessCommands();
	mCmdAllocator->Reset();//�L���[���N���A
	mCmdList->Reset(mCmdAllocator.Get(), nullptr);

	//�f�B�X�N���v�^
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	TextureInfo texture_info;
	texture_info.texture_resource_ = texResource;
	texture_info.format_ = (char)metadata.format;
	return texture_info;
}

void DX12Pimple::OpenRenderTarget(boost::shared_ptr<DX12DescriptorHeap> _heap, unsigned int _id)
{
	auto handle = _heap->GetCPUDescriptorHandle(_id);
	mCmdList->OMSetRenderTargets(1, &handle, false, nullptr);
}

void DX12Pimple::ClearRenderTarget(boost::shared_ptr<DX12DescriptorHeap> _heap, unsigned int _id, float _r, float _g, float _b, float _alpha)
{
	auto handle = _heap->GetCPUDescriptorHandle(_id);
	float clearcolor[] = { _r,_g,_b,_alpha };
	mCmdList->ClearRenderTargetView(handle, clearcolor, 0, nullptr);
}
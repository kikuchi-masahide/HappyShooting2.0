#include "DX12RootSignature.h"
#include "DX12Pimple.h"
#include "Log.h"

DX12RootSignature::DX12RootSignature(ComPtr<ID3D12Device> _device, DX12RootParameter& _descheap_rootparam, bool _hasSampler)
{
	D3D12_ROOT_SIGNATURE_DESC RSDesc = {};

	RSDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	//���[�g�p�����[�^�̍\����
	D3D12_ROOT_PARAMETER d3drootparameter = {};
	//�������ォ��delete[]���Ȃ���΂Ȃ�Ȃ��C�f�B�X�N���v�^�����W�\���̂̔z��̏W��
	std::vector<D3D12_DESCRIPTOR_RANGE*> ranges_array_to_delete;
	if (_descheap_rootparam.mDescRanges.size() > 0) {
		DX12RootParameter& param_from = _descheap_rootparam;
		//������ݒ肷�郋�[�g�p�����[�^�̍\����
		D3D12_ROOT_PARAMETER& param_to = d3drootparameter;
		param_to = {};
		//���̃��[�g�p�����[�^���f�B�X�N���v�^�e�[�u���ɕR�Â���
		param_to.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		//���̃��[�g�p�����^�̎������W�̐�
		param_to.DescriptorTable.NumDescriptorRanges = param_from.mDescRanges.size();
		//�V�F�[�_����̉���
		param_to.ShaderVisibility = mShaderVisibilityCorrespond[(unsigned char)param_from.mShaderVisibility];
		//�����W�̐���0�ȏ�̏ꍇ�C�����W�̔z������
		if (param_from.mDescRanges.size() > 0)
		{
			D3D12_DESCRIPTOR_RANGE* d3d_descriptor_range = new D3D12_DESCRIPTOR_RANGE[param_from.mDescRanges.size()];
			ranges_array_to_delete.push_back(d3d_descriptor_range);
			for (unsigned int range_ind = 0; range_ind < param_from.mDescRanges.size(); range_ind++)
			{
				DX12DescriptorRange& range_from = param_from.mDescRanges[range_ind];
				//������ݒ肷�郌���W�̍\����
				D3D12_DESCRIPTOR_RANGE& range_to = d3d_descriptor_range[range_ind];
				//�����W�̂��r���[�̎��
				range_to.RangeType = mDescRngTypeCorrespond[(unsigned char)range_from.mType];
				//�f�B�X�N���v�^�̐�
				range_to.NumDescriptors = range_from.mNumDescriptors;
				//�V�F�[�_���W�X�^�̂ǂ����炩
				range_to.BaseShaderRegister = range_from.mBaseShaderRegister;
				//�f�B�X�N���v�^�q�[�v�̂ǂ����炩
				range_to.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;//range_from.mBaseHeapRegister;
				range_to.RegisterSpace = 0;
			}
			param_to.DescriptorTable.pDescriptorRanges = d3d_descriptor_range;
		}
		//���[�g�p�����[�^�z����w��
		RSDesc.pParameters = &d3drootparameter;
		//���[�g�p�����[�^�̐�
		RSDesc.NumParameters = 1;
	}

	D3D12_STATIC_SAMPLER_DESC samplerDesc = {};
	if (_hasSampler) {
		//�T���v���[�ݒ�
		samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
		samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
		samplerDesc.MinLOD = 0.0f;
		samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
		samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;

		RSDesc.pStaticSamplers = &samplerDesc;
		RSDesc.NumStaticSamplers = 1;
	}
	else {
		RSDesc.pStaticSamplers = nullptr;
		RSDesc.NumStaticSamplers = 0;
	}

	ComPtr<ID3DBlob> rootSigBlob;
	ComPtr<ID3DBlob> errorBlob;
	auto result = D3D12SerializeRootSignature(&RSDesc, D3D_ROOT_SIGNATURE_VERSION_1_0,
		&rootSigBlob, &errorBlob);
	for (auto arr : ranges_array_to_delete)
	{
		delete[] arr;
	}
	if (FAILED(result)) {
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(), errorBlob->GetBufferSize(), errstr.begin());
		Log::OutputCritical(errstr);
		throw 0;
	}

	result = _device->CreateRootSignature(
		0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(mRootSignature.ReleaseAndGetAddressOf())
	);
	if (FAILED(result)) {
		Log::OutputCritical("RootSignature's initialization failed\n");
		throw 0;
	}
}

void DX12RootSignature::SetRootSignature(ComPtr<ID3D12GraphicsCommandList> _list)
{
	_list->SetGraphicsRootSignature(mRootSignature.Get());
}

D3D12_SHADER_VISIBILITY DX12RootSignature::mShaderVisibilityCorrespond[(unsigned char)DX12Config::RootParameterShaderVisibility::size] = {
	D3D12_SHADER_VISIBILITY_ALL,
	D3D12_SHADER_VISIBILITY_VERTEX,
	D3D12_SHADER_VISIBILITY_PIXEL
};

D3D12_DESCRIPTOR_RANGE_TYPE DX12RootSignature::mDescRngTypeCorrespond[(unsigned char)DX12Config::DescriptorRangeType::size] = {
	D3D12_DESCRIPTOR_RANGE_TYPE_CBV,
	D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
	D3D12_DESCRIPTOR_RANGE_TYPE_UAV
};

boost::shared_ptr<DX12RootSignature> DX12Pimple::CreateRootSignature(DX12RootParameter& _descheap_rootparam, bool _hasSampler)
{
	return boost::shared_ptr<DX12RootSignature>(new DX12RootSignature(
		mDevice, _descheap_rootparam, _hasSampler
	));
}

void DX12Pimple::SetRootSignature(boost::shared_ptr<DX12RootSignature> _root)
{
	_root->SetRootSignature(mCmdList);
}
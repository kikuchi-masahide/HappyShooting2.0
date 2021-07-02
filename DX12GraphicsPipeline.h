#pragma once

#include "DX12CommonInclude.h"
#include "DX12ConfigEnums.h"
#include "DX12VertexLayoutUnit.h"

class DX12Device;
class DX12ShaderObject;
class DX12RootSignature;
class DX12CmdList;

class DX12GraphicsPipeline final :public boost::noncopyable {
public:
	/// <summary>
	/// �O���t�B�b�N�X�p�C�v���C���̍쐬
	/// </summary>
	/// <param name="_vertexShader">���_�V�F�[�_</param>
	/// <param name="_pixelShader">�s�N�Z���V�F�[�_</param>
	/// <param name="_vertexLayout">���_���C�A�E�g</param>
	/// <param name="_primitive">�v���~�e�B�u�^</param>
	/// <param name="_numrt">�����_�[�^�[�Q�b�g��</param>
	DX12GraphicsPipeline(ComPtr<ID3D12Device> _device, boost::shared_ptr<DX12ShaderObject> _vertexShader,
		boost::shared_ptr<DX12ShaderObject> _pixelShader, DX12VertexLayout& _vertexLayout,
		DX12Config::PrimitiveTopologyType _primitive, UINT _numrt,
		boost::shared_ptr<DX12RootSignature> _rootsignature, LPCWSTR _name);
	void SetGraphicsPipeline(ComPtr<ID3D12GraphicsCommandList> _list);
private:
	ComPtr<ID3D12PipelineState> mState;
	static DXGI_FORMAT mVertexLayoutFormatCorrespond[(unsigned char)DX12Config::VertexLayoutFormat::size];
	static D3D12_INPUT_CLASSIFICATION mVertexLayoutInputClassificationCorrespond[(unsigned char)DX12Config::VertexLayoutInputClassification::size];
	static D3D12_PRIMITIVE_TOPOLOGY_TYPE mPrimitiveTopologyTypeCorrespond[(unsigned char)DX12Config::PrimitiveTopologyType::size];
};
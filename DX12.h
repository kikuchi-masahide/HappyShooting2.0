#pragma once

#include "DX12ConfigEnums.h"
#include "DX12VertexLayoutUnit.h"
#include "DX12RootParameter.h"
#include "DX12IShaderTransferable.h"
#include "DX12StructToShader.h"
class DX12Resource;
class DX12DescriptorHeap;
class DX12ShaderObject;
class DX12GraphicsPipeline;
class DX12RootSignature;
class DX12SwapChain;

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"DirectXTex.lib")
#pragma comment(lib,"d3dcompiler.lib")

class DX12Pimple;

class DX12 :public boost::noncopyable {
private:
	DX12Pimple* mPimple;
public:
	DX12();
	void Initialize();
	void CleanUp();
	~DX12();
	/// <summary>
	/// �f�B�X�N���v�^�q�[�v�����
	/// </summary>
	/// <param name="_type">�f�B�X�N���v�^�q�[�v�̎�� �ǂ̂悤�Ȏ�ނ̃f�B�X�N���v�^���i�[���邩</param>
	/// <param name="_vis">�V�F�[�_��������ۂ�</param>
	/// <param name="_num">���L�f�B�X�N���v�^�̐�</param>
	/// <returns>�f�B�X�N���v�^�q�[�v��\��shared_ptr</returns>
	boost::shared_ptr<DX12DescriptorHeap> CreateDescriptorHeap(DX12Config::DescriptorHeapType _type, DX12Config::DescriptorHeapShaderVisibility _vis, unsigned int _num);
	/// <summary>
	/// �e�t���[���ŕK�v�ȃR�}���h��ǉ������������ƌĂяo��
	/// </summary>
	void ProcessCommands();
	/// <summary>
	/// ���_�o�b�t�@�̍쐬
	/// </summary>
	/// <param name="_width">���_�o�b�t�@�̑S�T�C�Y</param>
	boost::shared_ptr<DX12Resource> CreateVertexBuffer(UINT64 _width);
	//���\�[�X�̃}�b�v
	void* Map(boost::shared_ptr<DX12Resource> _resource);
	void Unmap(boost::shared_ptr<DX12Resource> _resource);
	//�V�F�[�_�ǂݍ���
	boost::shared_ptr<DX12ShaderObject> LoadShader(LPCWSTR _filename, DX12Config::ShaderType _shaderType);
	/// <summary>
	/// �O���t�B�b�N�X�p�C�v���C���̍쐬
	/// </summary>
	/// <param name="_vertexShader">���_�V�F�[�_</param>
	/// <param name="_pixelShader">�s�N�Z���V�F�[�_</param>
	/// <param name="_vertexLayout">���_���C�A�E�g</param>
	/// <param name="_primitive">�v���~�e�B�u�^</param>
	/// <param name="_numrt">�����_�[�^�[�Q�b�g��</param>
	boost::shared_ptr<DX12GraphicsPipeline> CreateGraphicsPipeline(
		boost::shared_ptr<DX12ShaderObject> _vertexShader,
		boost::shared_ptr<DX12ShaderObject> _pixelShader, DX12VertexLayout& _vertexLayout,
		DX12Config::PrimitiveTopologyType _primitive, UINT _numrt,
		boost::shared_ptr<DX12RootSignature> _rootsignature);
	//���[�g�V�O�l�`���̍쐬(�b��)
	boost::shared_ptr<DX12RootSignature> CreateRootSignature(std::vector<DX12RootParameter>& _rootparams,bool _hasSampler = true);
	//�p�C�v���C���X�e�[�g�̃Z�b�g
	void SetGraphicsPipeline(boost::shared_ptr<DX12GraphicsPipeline> _pipeline);
	//���[�g�V�O�l�`���̃Z�b�g
	void SetRootSignature(boost::shared_ptr<DX12RootSignature> _root);
	//�v���~�e�B�u�̃R�}���h���X�g�ւ̃Z�b�g
	void SetPrimitiveTopology(DX12Config::PrimitiveTopology _prim);
	/// <summary>
	/// ���_�o�b�t�@���R�}���h���X�g�փZ�b�g
	/// </summary>
	/// <param name="_allsize">���_�o�b�t�@�S�̂̃T�C�Y</param>
	/// <param name="_sizepervertex">1���_�o�b�t�@������̃T�C�Y</param>
	void SetVertexBuffers(boost::shared_ptr<DX12Resource> _resource, unsigned int _slotid,
		SIZE_T _allsize, SIZE_T _sizepervertex);
	/// <summary>
	/// �R�}���h���X�g�֕`�施�߂𓊂���
	/// </summary>
	/// <param name="_indexnumperinst">�C���X�^���X���Ƃ́C���_�C���f�b�N�X��</param>
	/// <param name="_instnum">�C���X�^���X��</param>
	/// <param name="_indoffset">���_�C���f�b�N�X�̃I�t�Z�b�g</param>
	/// <param name="_vdataoffset">���_�f�[�^�̃I�t�Z�b�g</param>
	/// <param name="_instoffset">�C���X�^���X�̃I�t�Z�b�g</param>
	void DrawIndexedInstanced(UINT _indexnumperinst, UINT _instnum, UINT _indoffset,
			UINT _vdataoffset, UINT _instoffset);
	/// <summary>
	/// �r���[�|�[�g�̃Z�b�g
	/// </summary>
	/// <param name="_widthpx">����px</param>
	/// <param name="_heightpx">������px</param>
	void SetViewports(UINT _widthpx, UINT _heightpx, int _topleftx, int _toplefty,
		float _maxdepth, float _mindepth);
	/// <summary>
	/// �V�U�[��`�̃Z�b�g
	/// </summary>
	void SetScissorrect(float _top, float _bottom, float _left, float _right);
	/// <summary>
	/// �Ώۃ��\�[�X�𒸓_�C���f�b�N�X�o�b�t�@�Ɏw��
	/// </summary>
	/// <param name="_vertnum">�C���f�b�N�X�o�b�t�@�̊܂ޑS���_��</param>
	void SetIndexBuffers(boost::shared_ptr<DX12Resource> _resource,unsigned int _vertnum);
	/// <summary>
	/// �C���f�b�N�X�o�b�t�@�̍쐬
	/// </summary>
	/// <param name="_size">�����_��</param>
	boost::shared_ptr<DX12Resource> CreateIndexBuffer(unsigned int _vertnum);
	/// <summary>
	/// �e�N�X�`����ǂݍ��݃f�B�X�N���v�^���쐬
	/// </summary>
	/// <param name="_desc">�f�B�X�N���v�^�q�[�v</param>
	/// <param name="_num">�f�B�X�N���v�^�q�[�v�̉��ԖڂɃf�B�X�N���v�^���쐬���邩</param>
	/// <returns>GPU��̓ǂݎ���p�o�b�t�@������DX12Resource</returns>
	boost::shared_ptr<DX12Resource> LoadTexture(const wchar_t* _filename, boost::shared_ptr<DX12DescriptorHeap> _desc,unsigned int _num);
	/// <summary>
	/// �R�}���h���X�g�ɑ΂���f�B�X�N���v�^�q�[�v�̎w��
	/// </summary>
	void SetDescriptorHeap(boost::shared_ptr<DX12DescriptorHeap> _descHeap);
	/// <summary>
	/// �f�B�X�N���v�^�e�[�u���̐ݒ�
	/// </summary>
	/// <param name="_rootParamIndex">���Ԃ̃��[�g�p�����[�^��ݒ肷�邩</param>
	/// <param name="_descHeap">�f�B�X�N���v�^�q�[�v</param>
	/// <param name="_descHeapIndex">�f�B�X�N���v�^�q�[�v�̉��Ԃ�ݒ肷�邩</param>
	void SetGraphicsRootDescriptorTable(unsigned int _rootParamIndex, boost::shared_ptr<DX12DescriptorHeap> _descHeap, unsigned int _descHeapIndex);
	/// <summary>
	/// ���\�[�X�o���A�����X�g�ɃZ�b�g
	void SetResourceBarrier(boost::shared_ptr<DX12Resource> _resource, DX12Config::ResourceBarrierState _before, DX12Config::ResourceBarrierState _after);
	boost::shared_ptr<DX12SwapChain> CreateSwapChain(HWND _hwnd, UINT _width, UINT _height);
	/// <summary>
	/// �X���b�v�`�F�[���̃t���b�v
	/// </summary>
	void FlipSwapChain(boost::shared_ptr<DX12SwapChain> _swapchain);
	/// <summary>
	/// �����_�[�^�[�Q�b�g���J��(���\�[�X�o���A�̐ݒ荞��)
	/// </summary>
	void OpenRenderTarget(boost::shared_ptr<DX12SwapChain> _swapchain);
	/// <summary>
	/// �����_�[�^�[�Q�b�g�����(���\�[�X�o���A�̐ݒ荞��)
	/// </summary>
	void CloseRenderTarget(boost::shared_ptr<DX12SwapChain> _swapchain);
	/// <summary>
	/// �w��F�Ń����_�[�^�[�Q�b�g���N���A
	/// </summary>
	void ClearRenderTarget(boost::shared_ptr<DX12SwapChain> _swapchain, float _r, float _g, float _b);
	/// <summary>
	/// �w��̑傫���E�F������̃e�N�X�`�����쐬(������Ԃ�PIXEL_SHADER_RESOURCE)
	/// </summary>
	boost::shared_ptr<DX12Resource> CreateClearTexture(UINT64 _width, UINT64 _height, float _r, float _g, float _b, float _alpha);
	/// <summary>
/// �w��f�B�X�N���v�^�q�[�v��ɂ��̃��\�[�X�̃����_�[�^�[�Q�b�g�r���[�����
/// </summary>
/// <param name="_n">�f�B�X�N���v�^�q�[�v�̉��ԖڂɃr���[����邩</param>
	void CreateRenderTargetView(boost::shared_ptr<DX12Resource> _resource, boost::shared_ptr<DX12DescriptorHeap> _descheap, int _n);
	/// <summary>
	/// �w��f�B�X�N���v�^�q�[�v��ɂ��̃��\�[�X�̃����_�[�^�[�Q�b�g�r���[�����
	/// </summary>
	/// <param name="_n">�f�B�X�N���v�^�q�[�v�̉��ԖڂɃr���[����邩</param>
	void CreateShaderResourceView(boost::shared_ptr<DX12Resource> _resource, boost::shared_ptr<DX12DescriptorHeap> _descheap, int _n);
	//�f�B�X�N���v�^�q�[�v��ID���w�肵�ă����_�[�^�[�Q�b�g��open(�o���A�̐ݒ�͖���)
	void OpenRenderTarget(boost::shared_ptr<DX12DescriptorHeap> _heap, unsigned int _id);
	void ClearRenderTarget(boost::shared_ptr<DX12DescriptorHeap> _heap, unsigned int _id, float _r, float _g, float _b, float _alpha);
	/// <summary>
	/// �萔�o�b�t�@���쐬
	/// </summary>
	/// <param name="_bytesize">�K�v�T�C�Y(256�A���C�������g�͕K�v�Ȃ�)</param>
	boost::shared_ptr<DX12Resource> CreateConstBuffer(DX12Config::ResourceHeapType _heaptype,UINT64 _bytesize);
	/// <summary>
	/// �|�C���^_map�ɍs����R�s�[ ���̂Ƃ��s��͎����I�ɓ]�u�����
	/// </summary>
	void Copy4x4Matrix(void* _map, MatVec::Matrix4x4 _mat);
	/// <summary>
	/// �f�B�X�N���v�^�q�[�v_descheap��_n�ԖڃX���b�g�ɒ萔�o�b�t�@_resource�ɑ΂���CBV���쐬
	/// </summary>
	void CreateConstBufferView(boost::shared_ptr<DX12Resource> _resource, boost::shared_ptr<DX12DescriptorHeap> _descheap, int _n);
	/// <summary>
	/// �C���f�b�N�X�o�b�t�@�������Ȃ��C���X�^���X��`�悷��
	/// </summary>
	/// <param name="vertex_count_per_instance">�`�悷�钸�_�̐�</param>
	/// <param name="instance_count">�`�悷��C���X�^���X�̐�</param>
	/// <param name="start_vertex_location">�ŏ��̒��_�̓Y����</param>
	/// <param name="start_instance_location"></param>
	void DrawInstanced(UINT vertex_count_per_instance, UINT instance_count, UINT start_vertex_location, UINT start_instance_location);
};
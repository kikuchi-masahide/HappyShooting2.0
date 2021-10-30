#pragma once
/// <summary>
/// �N���XDX12�����C���^�[�t�F�[�X�ŗp����enum
/// </summary>

namespace DX12Config {
	//�f�B�X�N���v�^�q�[�v�̎��
	enum class DescriptorHeapType :unsigned char {
		RTV,
		CBV_SRV_UAV,
		DSV,
		size
	};
	//�V�F�[�_����̉��͈͂Ɋւ���萔
	enum class DescriptorHeapShaderVisibility :unsigned char {
		NONE,
		SHADER_VISIBLE,
		size
	};
	//���\�[�X�̃q�[�v��CPU����̃A�N�Z�X�̉s�̐ݒ�
	enum class ResourceHeapType :unsigned char {
		DEFAULT,//CPU����A�N�Z�X�ł��Ȃ�
		UPLOAD,//CPU����A�N�Z�X�ł���
		READBACK,//CPU����ǂݎ���
		size
	};
	//�V�F�[�_�̃^�C�v
	enum class ShaderType :unsigned char {
		VERTEX,
		PIXEL,
		size
	};
	//���_���C�A�E�g�̏��t�H�[�}�b�g
	enum class VertexLayoutFormat :unsigned char {
		R32G32B32_FLOAT,
		R8G8B8A8_UNORM,
		R32G32_FLOAT,
		R32_UINT,
		size
	};
	//���_���C�A�E�g��input_classificastion
	enum class VertexLayoutInputClassification :unsigned char {
		INPUT_CLASSIFICATION_PER_VERTEX_DATA,
		INPUT_CLASSIFICATION_PER_INSTANCE_DATA,
		size
	};
	//�R�}���h���X�g�Ŏw�肷��v���~�e�B�u�g�|���W(�\���v�f�̎w��)
	enum class PrimitiveTopology :unsigned char {
		POINT,
		LINELIST,//�Ɨ����������̏W��
		LINESTRIP,//�O�̒��_�ƂȂ����
		TRIANGLELIST,//�Ɨ������O�p�`�̏W��
		TRIANGLESTRIP,//�O�̎O�p�`�ƂȂ������O�p�`�̏W����
		size
	};
	//�O���t�B�b�N�X�p�C�v���C���Ŏw�肷��v���~�e�B�u�g�|���W�^�C�v
	enum class PrimitiveTopologyType :unsigned char {
		POINT,
		LINE,
		TRIANGLE,
		size
	};
	//�f�B�X�N���v�^�����W�̃^�C�v
	enum class DescriptorRangeType :unsigned char {
		CBV,
		SRV,
		UAV,
		size
	};
	//���[�g�p�����[�^�̃V�F�[�_�[����̌����
	enum class RootParameterShaderVisibility :unsigned char {
		ALL,
		VERTEX,
		PIXEL,
		size
	};
	//���\�[�X�o���A�̑J�ڑO��̒萔
	enum class ResourceBarrierState :unsigned char {
		PRESENT,
		RENDER_TARGET,
		COPY_DEST,
		PIXEL_SHADER_RESOURCE,
		size
	};
}

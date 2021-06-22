#pragma once
#include "Layer.h"
#include "Game.h"
#include "ComponentHandle.h"
#include "MainSceneDrawComponent.h"

class MyselfPosAndAngleComponent;

class MainSceneBaseLayer :public Layer
{
public:
	MainSceneBaseLayer(MainScene* scene, ComponentHandle<MyselfPosAndAngleComponent> myself_pos_component);
	virtual ~MainSceneBaseLayer();
	void Draw();
	/// <summary>
	/// Draw()����Ăяo�����C�y���|���S�������ۂɃE�B���h�E�֕`�悷�邽�߂̊֐�
	/// �y���|���S���́C�Scomponent�̕`�悪�ς񂾏�ԂɂȂ��Ă���C�V�F�[�_�[���\�[�X��Ԃɂ���o���A���s��
	/// </summary>
	virtual void UniqueDraw() = 0;
	/// <summary>
	/// MainScene����A�N�e�B�u�ɂȂ�O��tick�ɌĂяo�����D���̃��C���[���A�N�e�B�u�ɂ���
	/// (�A�N�e�B�u�ȏ�ԂŌĂяo�����ƃJ�E���^���Z�b�g��0�̏�Ԃ���X�^�[�g)
	/// </summary>
	void SetActive();
	void SetUnActive();
	/// <summary>
	/// MainScene����Ăяo�����CDraw�R�[�����K�v�ȃR���|�[�l���g�̒ǉ��֐�
	/// </summary>
	void AddComponent(ComponentHandle<MainSceneDrawComponent> component);
	/// <summary>
	/// layer_t_(�A�N�e�B�u�ɂȂ��Ă���̎���)���擾
	/// </summary>
	unsigned int GetLayert();
protected:
	//�y���|���S��
	boost::shared_ptr<DX12Resource> pera_texture_;
	//�y���|���S����RTV;
	boost::shared_ptr<DX12DescriptorHeap> pera_rtv_;
	//�y���|���S����SRV;
	boost::shared_ptr<DX12DescriptorHeap> pera_srv_;
	Game& GetGame();
	MainScene* const scene_;
	//���̃R���|�[�l���g�ɖ�tick���C���[�̕ό`��ʒm
	ComponentHandle<MyselfPosAndAngleComponent> myself_pos_component_;
private:
	std::vector<ComponentHandle<MainSceneDrawComponent>> draw_components_;
	//���̃��C���[���A�N�e�B�u�ɂȂ��Ă��牽�x�ڂ̃t���[����
	//(1��ڂ�UniqueDraw���Ăяo���ꂽ�Ƃ���0)
	unsigned int layer_t_;
	//���̃��C���[���A�N�e�B�u���ۂ�
	bool is_active_;
	//MainSceneBaseLayer�̃O���t�B�b�N�X������
	void GraphicsInit();
};
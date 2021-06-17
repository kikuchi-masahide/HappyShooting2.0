#pragma once
#include "Layer.h"
#include "ComponentHandle.h"
#include "MainSceneDrawComponent.h"

class MainSceneBaseLayer :public Layer
{
public:
	MainSceneBaseLayer(Scene* scene, boost::shared_ptr<std::set<void*>> hset);
	virtual ~MainSceneBaseLayer();
	void Draw();
	/// <summary>
	/// Draw()����Ăяo�����C�y���|���S�������ۂɃE�B���h�E�֕`�悷�邽�߂̊֐�
	/// �y���|���S���́C�Scomponent�̕`�悪�ς񂾏�ԂɂȂ��Ă���
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
private:
	std::vector<ComponentHandle<MainSceneDrawComponent>> draw_components_;
	//���̃��C���[���A�N�e�B�u���ۂ�
	bool is_active_;
	//���̃��C���[���A�N�e�B�u�ɂȂ��Ă��牽�x�ڂ̃t���[����
	//(1��ڂ�UniqueDraw���Ăяo���ꂽ�Ƃ���0)
	unsigned int layer_t_;
};
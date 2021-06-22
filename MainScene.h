#pragma once
#include "Scene.h"
#include "LayerHandle.h"
#include "MainSceneBaseLayer.h"

class MainScene :public Scene
{
public:
	MainScene(Game* game);
	void UniqueUpdate();
	void UniqueOutput();
	~MainScene();
	/// <summary>
	/// ���A�N�e�B�u�ȃ��C���[�ɕ`��R���|�[�l���g��ǉ�
	/// </summary>
	void AddComponentToLayer(ComponentHandle<MainSceneDrawComponent> component);
	/// <summary>
	/// ��tick���炱�̃t���[����L��������
	/// </summary>
	void SwapLayer(unsigned int ind);
private:
	//�����Ă��郌�C���[�̓��`�悷�����
	LayerHandle<MainSceneBaseLayer> active_layer_;
	//�g���郌�C���[�̈ꗗ
	LayerHandle<MainSceneBaseLayer> available_layers_[1];
	//����tick����g�����C���[(none:999)
	unsigned int layer_from_next_tick_;
	//���@�I�u�W�F�N�g�̃n���h��
	GameObjectHandle myself_handle_;
	//���@�̈ʒu�p�x�ύX�R���|�[�l���g
	ComponentHandle<MyselfPosAndAngleComponent> myself_pos_angle_handle_;
	//�V�[���Ɏ��@��ǉ�����
	void AddMyself();
};
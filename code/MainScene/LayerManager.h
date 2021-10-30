#pragma once
#include "MainSceneBaseLayer.h"
#include "../Engine/Layer.h"
#include "Math.h"
#include "../Engine/Component.h"

class MainSceneDrawComponent;
class Scene;

class LayerManager
{
public:
	LayerManager(Scene* scene);
	~LayerManager();
	/// <summary>
	/// ���A�N�e�B�u�ȃ��C���[�ɕ`��R���|�[�l���g��ǉ�
	/// </summary>
	void AddComponentToLayer(ComponentHandle<MainSceneDrawComponent> component);
	/// <summary>
	/// ��tick���炱�̃t���[����L��������
	/// </summary>
	void SwapLayer(unsigned int ind);
	/// <summary>
	/// ���ݗL���ȃ��C���[�̕ό`�s��𓾂�
	/// </summary>
	MatVec::Matrix4x4 GetLayerTransform();
	/// <summary>
	/// Scene��PriorUniqueUpdate�ŌĂяo���Ă��炤
	/// </summary>
	void PriorUniqueUpdate();
	//�eScene(MainSceneDrawComponent�����g����悤��)
	Scene* const scene_;
private:
	//�����Ă��郌�C���[�̓��`�悷�����
	LayerHandle<MainSceneBaseLayer> active_layer_;
	//�g���郌�C���[�̈ꗗ
	LayerHandle<MainSceneBaseLayer> available_layers_[1];
	//����tick����g�����C���[(none:999)
	unsigned int layer_from_next_tick_;
};


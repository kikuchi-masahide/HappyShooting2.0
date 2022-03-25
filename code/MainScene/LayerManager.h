#pragma once
#include "MainSceneBaseLayer.h"
#include "../Engine/Layer.h"
#include "Math.h"
#include "../Engine/Component.h"

class MainSceneDrawComponent;
class Scene;

//draw_components_�̕ۑ��P��
//(MainSceneDrawComponent�}�����Cmultiset�̂�������component�͏������ꂽ��ԂŋN�����Ă��邽�߁C���炩����z��ۑ����Ă���)
class DrawComponentUnit {
public:
	DrawComponentUnit(ComponentHandle<MainSceneDrawComponent> comp);
	ComponentHandle<MainSceneDrawComponent> comp_;
	double z_;
};

//draw_components_�p�̔�r�֐�
class DrawComponentCompare {
public:
	bool operator()(const DrawComponentUnit& left, const DrawComponentUnit& right) const;
};
using DrawComponentsMultiset = std::multiset<DrawComponentUnit, DrawComponentCompare>;

class LayerManager
{
public:
	LayerManager(Scene* scene);
	~LayerManager();
	//�����C���[�̏��������܂Ƃ߂čs��
	//TODO:�R���X�g���N�^�ŏ��������ł��������悳���ȋC�����邪�C���@�n���h���̓n�����Ȃǂ̊֌W�łǂ����Ă���ɉ񂳂���𓾂Ȃ� �s����
	void InitLayers();
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
	//���̃I�u�W�F�N�g�����@�Ƃ��Ďw��
	void SetMyselfHandle(GameObjectHandle handle);
private:
	//�����Ă��郌�C���[�̓��`�悷�����
	LayerHandle<MainSceneBaseLayer> active_layer_;
	//�g���郌�C���[�̈ꗗ
	LayerHandle<MainSceneBaseLayer> available_layers_[5];
	//����tick����g�����C���[(none:999)
	unsigned int layer_from_next_tick_;
	GameObjectHandle myself_;
	//�Ăяo��DrawComponents_��multiset
	DrawComponentsMultiset draw_components_;
};


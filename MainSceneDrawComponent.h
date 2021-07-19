#pragma once
#include "Component.h"

class LayerManager;
class MainScene;

class MainSceneDrawComponent :public Component
{
public:
	MainSceneDrawComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager);
	void Update() final;
	virtual ~MainSceneDrawComponent();
	/// <summary>
	/// Update�ŃV�[���Ɏ����̃n���h����������ꂽ�ヌ�C���[����Ăяo�����C�`��@�\�{�̂�S���֐��DSRV�͊J���Ă���Ƃ��Ă悢�D
	/// </summary>
	virtual void Draw() = 0;
protected:
	const boost::shared_ptr<LayerManager> layer_manager_;
};
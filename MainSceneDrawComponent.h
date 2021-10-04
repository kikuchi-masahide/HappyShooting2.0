#pragma once
#include "Component.h"

class LayerManager;
class MainScene;

class MainSceneDrawComponent :public Component
{
public:
	MainSceneDrawComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager,double z);
	void Update() final;
	virtual ~MainSceneDrawComponent();
	/// <summary>
	/// Update�ŃV�[���Ɏ����̃n���h����������ꂽ�ヌ�C���[����Ăяo�����C�`��@�\�{�̂�S���֐��DSRV�͊J���Ă���Ƃ��Ă悢�D
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// �e�N�X�`����z���W(����n�Ȃ̂ő傫���قǉ�)
	/// </summary>
	const double z_;
protected:
	const boost::shared_ptr<LayerManager> layer_manager_;
};
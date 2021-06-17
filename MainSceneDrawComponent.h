#pragma once
#include "Component.h"

class MainScene;

class MainSceneDrawComponent :public Component
{
public:
	MainSceneDrawComponent(GameObject* owner, boost::shared_ptr<std::set<void*>> hset,MainScene* scene);
	void Update();
	virtual ~MainSceneDrawComponent();
	/// <summary>
	/// Update�ŃV�[���Ɏ����̃n���h����������ꂽ�ヌ�C���[����Ăяo�����C�`��@�\�{�̂�S���֐��DSRV�͊J���Ă���Ƃ��Ă悢�D
	/// </summary>
	virtual void Draw() = 0;
protected:
	MainScene* scene_;
};
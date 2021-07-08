#pragma once
#include "CollisionComponent.h"

#include "CircleGeometry.h"
#include "MainScene.h"
#include "GameObject.h"

class EnemyHealthComponent;

/// <summary>
/// enemy1�{�̗p�̓����蔻��
/// ���@�C���@�e�ɓ���������̗͌�
/// </summary>
class Enemy1CollisionComponent
	:public CollisionComponent
{
public:
	Enemy1CollisionComponent(MainScene* scene,GameObjectHandle object,ComponentHandle<EnemyHealthComponent> health);
	~Enemy1CollisionComponent();
	void Update() override;
	void AddGeometryToManager(CollisionManager& manager) override;
	//�Փˎ��̃_���[�W
	static constexpr double damage_ = 200;
private:
	//����̉~�̕��̉~�`�����蔻��
	CircleGeometry circle_around_[3];
	//���S�̉~�̕��̉~�`�����蔻��
	CircleGeometry circle_center_;
	MainScene* scene_;
	GameObjectHandle object_;
	//�_���[�W�񍐗p
	ComponentHandle<EnemyHealthComponent> health_component_;
};


#pragma once
#include "EnemyBodyCollisionComponent.h"

#include "CircleGeometry.h"
#include "MainScene.h"
#include "GameObject.h"

class EnemyHealthComponent;
class ScoreManager;

/// <summary>
/// enemy1�{�̗p�̓����蔻��
/// ���@�C���@�e�ɓ���������̗͌�
/// </summary>
class Enemy1CollisionComponent
	:public EnemyBodyCollisionComponent
{
public:
	Enemy1CollisionComponent(GameObjectHandle object, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<ScoreManager> score_manager, ComponentHandle<EnemyHealthComponent> health);
	~Enemy1CollisionComponent();
	void Update() override;
	//�Փˎ��̃_���[�W
	static constexpr double damage_ = 200;
private:
	//����̉~�̕��̉~�`�����蔻��
	CircleGeometry circle_around_[3];
	//���S�̉~�̕��̉~�`�����蔻��
	CircleGeometry circle_center_;
};


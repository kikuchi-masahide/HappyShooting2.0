#pragma once
#include "Scene.h"
#include "LayerHandle.h"
#include "MainSceneBaseLayer.h"
#include "CollisionManager.h"
#include "LayerManager.h"

class MainScene :public Scene
{
public:
	MainScene(Game* game);
	void PriorUniqueUpdate() override;
	void PosteriorUniqueUpdate() override;
	void PriorUniqueOutput() override;
	void PosteriorUniqueOutput() override;
	~MainScene();
	//���@���܂܂�����CollisionManager
	CollisionManager collision_manager_;
	//�X�R�A�����Z
	void AddScore(int add);
	int GetScore() const;
	/// <summary>
	/// ���@���_������G�@�̒ǉ�
	/// </summary>
	// TEST:�G�@��ǉ�������e�X�g
	void AddDirectableEnemy(GameObjectHandle enemy);
	/// <summary>
	/// ���@����ł��߂��G�@��Ԃ�(�N�����Ȃ��Ȃ�null)
	/// </summary>
	GameObjectHandle GetNearestEnemy();
	//TODO:���̂�������
	boost::shared_ptr<LayerManager> GetLayerManager();
private:
	//���@�I�u�W�F�N�g�̃n���h��
	GameObjectHandle myself_handle_;
	//���@�̈ʒu�p�x�ύX�R���|�[�l���g
	ComponentHandle<MyselfPosAndAngleComponent> myself_pos_angle_handle_;
	//�V�[���Ɏ��@��ǉ�����
	void AddMyself();
	//���݂̃X�R�A
	int score_;
	std::list<GameObjectHandle> enemies_;
	//�O�t���[���I�����ł́C���@�ɍł��߂������G�@
	GameObjectHandle nearest_enemy_;
	//�t���[���I���Ŏ����ɍł��߂��G�@��������
	void FindNearestEnemy();
	//enemy1�Q�݂̂�����ŏ�������
	void PrepareEnemy1();
	boost::shared_ptr<LayerManager> layer_manager_;
};
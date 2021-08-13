#pragma once
#include "Scene.h"
#include "LayerHandle.h"
#include "MainSceneBaseLayer.h"
#include "CollisionManager.h"
#include "LayerManager.h"
#include "ScoreManager.h"
#include "EnemyWaveManager.h"

class MainScene :public Scene
{
public:
	MainScene(Game* game);
	void PriorUniqueUpdate() override;
	void PosteriorUniqueUpdate() override;
	void PriorUniqueOutput() override;
	void PosteriorUniqueOutput() override;
	~MainScene();
	boost::shared_ptr<LayerManager> GetLayerManager();
	boost::shared_ptr<ScoreManager> GetScoreManager();
	boost::shared_ptr<EnemyWaveManager> GetEnemyWaveManager();
	boost::shared_ptr<CollisionManager> GetCollisionManager();
	GameObjectHandle GetMyselfHandle();
private:
	//���@�̈ʒu�p�x�ύX�R���|�[�l���g
	ComponentHandle<MyselfPosAndAngleComponent> myself_pos_angle_handle_;
	//�V�[���Ɏ��@��ǉ�����
	void AddMyself();
	//���݂̃X�R�A
	int score_;
	std::list<GameObjectHandle> enemies_;
	//�O�t���[���I�����ł́C���@�ɍł��߂������G�@
	GameObjectHandle nearest_enemy_;
	boost::shared_ptr<LayerManager> layer_manager_;
	boost::shared_ptr<ScoreManager> score_manager_;
	boost::shared_ptr<EnemyWaveManager> enemy_wave_manager_;
	boost::shared_ptr<CollisionManager> collision_manager_;
	//���@�I�u�W�F�N�g�̃n���h��
	GameObjectHandle myself_handle_;
};
#include "MainScene.h"

#include "MainSceneBasicLayer.h"
#include "MainSceneUIScreen.h"
#include "DrawTextureComponent.h"
#include "MyselfPosAndAngleComponent.h"
#include "MyselfMediatorComponent.h"
#include "DrawNormalBulletComponent.h"
#include "EnemyWaveManager.h"

MainScene::MainScene(Game* game)
	:Scene(game)
{
	//���C���[
	layer_manager_ = boost::shared_ptr<LayerManager>(new LayerManager(this));
	//�X�R�A
	score_manager_ = boost::shared_ptr<ScoreManager>(new ScoreManager);
	collision_manager_ = boost::shared_ptr<CollisionManager>(new CollisionManager());

	//���@�ǉ�
	AddMyself();

	enemy_wave_manager_ = boost::shared_ptr<EnemyWaveManager>(new EnemyWaveManager(this));

	////enemy1�Q�ǉ�
	//PrepareEnemy1();


	//UIScreen
	AddUIScreen<MainSceneUIScreen>(score_manager_);
}

void MainScene::PriorUniqueUpdate()
{
	//���C���[�̓���ւ�
	layer_manager_->PriorUniqueUpdate();
}

void MainScene::PosteriorUniqueUpdate()
{
}

void MainScene::PriorUniqueOutput()
{
}

void MainScene::PosteriorUniqueOutput()
{
	//�SUpdate���I��������Ɠ����蔻�肾�����������C���ʂׂ��I�u�W�F�N�g�����Ȃ���
	collision_manager_->TraverseAll();
	enemy_wave_manager_->Update();
}

MainScene::~MainScene()
{
}

boost::shared_ptr<LayerManager> MainScene::GetLayerManager()
{
	return layer_manager_;
}

boost::shared_ptr<ScoreManager> MainScene::GetScoreManager()
{
	return score_manager_;
}

boost::shared_ptr<EnemyWaveManager> MainScene::GetEnemyWaveManager()
{
	return enemy_wave_manager_;
}

boost::shared_ptr<CollisionManager> MainScene::GetCollisionManager()
{
	return collision_manager_;
}

GameObjectHandle MainScene::GetMyselfHandle()
{
	return myself_handle_;
}

void MainScene::AddMyself()
{
	myself_handle_ = AddObject(MatVec::Vector2(0, -275), 1.0, 0.0);
	//���̃R���|�[�l���g�̒ǉ��̓��f�B�G�[�^�ɔC����
	myself_handle_->AddUpdateComponent<MyselfMediatorComponent>(layer_manager_,score_manager_,collision_manager_);
}

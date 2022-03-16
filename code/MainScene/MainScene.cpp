#include "MainScene.h"

#include "MainSceneBasicLayer.h"
#include "MainSceneUIScreen.h"
#include "DrawTextureComponent.h"
#include "MyselfPosAndAngleComponent.h"
#include "MyselfMediatorComponent.h"
#include "DrawNormalBulletComponent.h"
#include "EnemyWaveManager.h"
#include "CollisionUIScreen.h"
#include "EnemyWave6.h"
#include "MyselfMediatorComponent.h"

MainScene::MainScene(Game* game)
	:Scene(game)
{
	Log::OutputTrivial("start MainScene;");
	//���C���[
	layer_manager_ = boost::shared_ptr<LayerManager>(DBG_NEW LayerManager(this));
	//�X�R�A
	score_manager_ = boost::shared_ptr<ScoreManager>(DBG_NEW ScoreManager);


	////enemy1�Q�ǉ�
	//PrepareEnemy1();


	//UIScreen
	AddUIScreen<MainSceneUIScreen>(score_manager_);

	CollisionUIScreen* collision_ui = AddUIScreen<CollisionUIScreen>();
	collision_manager_ = boost::shared_ptr<CollisionManager>(DBG_NEW CollisionManager(collision_ui));

	enemy_wave_manager_ = boost::shared_ptr<EnemyWaveManager>(DBG_NEW EnemyWaveManager(this));
	enemy_wave_manager_->SetWave(boost::shared_ptr<EnemyWaveBase>(DBG_NEW EnemyWave6(this)));

	//���@�ǉ�
	AddMyself();
	layer_manager_->SetMyselfHandle(mediator_->mObj);
	layer_manager_->InitLayers();

	//TODO:�f�o�b�O���̑Q���I�ȏ���
	//Release�Ȃ炱��������AEnemyWave6�̂��̕���L��������
	//�}�W�ł����܂��̏������ǂ��ɂ����Ȃ��ƃ��o��
	SetMyselfArmor2();

}

void MainScene::PriorUniqueUpdate()
{
	//���C���[�̓���ւ�
	layer_manager_->PriorUniqueUpdate();
}

void MainScene::PosteriorUniqueUpdate()
{
	//�SUpdate���I��������Ɠ����蔻�肾�����������C���ʂׂ��I�u�W�F�N�g�����Ȃ���
	collision_manager_->TraverseAll();
	enemy_wave_manager_->Update();
}

void MainScene::PriorUniqueOutput()
{
}

void MainScene::PosteriorUniqueOutput()
{
}

MainScene::~MainScene()
{
	Log::OutputTrivial("end MainScene;");
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
	return mediator_->mObj;
}

void MainScene::SetMyselfArmor2()
{
	mediator_->SetMyselfArmor2();
}

void MainScene::AddMyself()
{
	auto obj = AddObject(MatVec::Vector2(0, -275), 1.0, 0.0);
	//���̃R���|�[�l���g�̒ǉ��̓��f�B�G�[�^�ɔC����
	mediator_ = obj->AddUpdateComponent<MyselfMediatorComponent>(layer_manager_,score_manager_,collision_manager_, enemy_wave_manager_);
}

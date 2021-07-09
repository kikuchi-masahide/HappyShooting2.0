#include "MainScene.h"

#include "MainSceneBasicLayer.h"
#include "MainSceneUIScreen.h"
#include "DrawTextureComponent.h"
#include "MyselfPosAndAngleComponent.h"
#include "MyselfMediatorComponent.h"
#include "DrawNormalBulletComponent.h"
#include "LinearMoveComponent.h"
#include "LinearRotateComponent.h"
#include "Enemy1CollisionComponent.h"
#include "EnemyHealthComponent.h"
#include "DrawTextureComponent.h"

MainScene::MainScene(Game* game)
	:Scene(game),layer_from_next_tick_(999)
{
	//���@�ǉ�
	AddMyself();

	//���C���[
	auto layer0 = AddLayer<MainSceneBasicLayer>(this,myself_pos_angle_handle_);
	available_layers_[0] = static_cast<LayerHandle<MainSceneBaseLayer>>(layer0);
	//�n�߂̓��C���[0��L����
	active_layer_ = available_layers_[0];
	active_layer_->SetActive();

	//UIScreen
	AddUIScreen<MainSceneUIScreen>(this);

	//enemy1 test
	double dist = sqrt(
		300 * 300 + 450 * 450
	);
	double speedx = -dist * 2 / 600;
	double speedy = -dist * 3 / 600;
	auto e1 = AddObject(MatVec::Vector2(0, 450) - MatVec::Vector2(speedx, speedy) * 5, 1.0, 0.0);
	e1->AddUpdateComponent<LinearMoveComponent>(e1, MatVec::Vector2(speedx, speedy), dist / 120 * 5);
	e1->AddUpdateComponent<LinearRotateComponent>(e1, PI / 60);
	auto health = e1->AddUpdateComponent<EnemyHealthComponent>(this, e1, 100);
	e1->AddUpdateComponent<Enemy1CollisionComponent>(this, e1, health);
	auto texture = e1->AddOutputComponent<DrawTextureComponent>(this, 7, e1);
	texture->width_ = 40;
	texture->height_ = 40;
}

void MainScene::PriorUniqueUpdate()
{
	//���C���[�̓���ւ�
	if (layer_from_next_tick_ != 999)
	{
		active_layer_->SetUnActive();
		active_layer_ = available_layers_[layer_from_next_tick_];
		active_layer_->SetActive();
		layer_from_next_tick_ = 999;
	}

	collision_manager_.TraverseAll();
}

void MainScene::PosteriorUniqueUpdate()
{
	FindNearestEnemy();
}

void MainScene::PriorUniqueOutput()
{
}

void MainScene::PosteriorUniqueOutput()
{
}

MainScene::~MainScene()
{
}

void MainScene::AddComponentToLayer(ComponentHandle<MainSceneDrawComponent> component)
{
	active_layer_->AddComponent(component);
}

void MainScene::SwapLayer(unsigned int ind)
{
	layer_from_next_tick_ = ind;
}

void MainScene::AddScore(int add)
{
	score_ += add;
}

int MainScene::GetScore() const
{
	return score_;
}

void MainScene::AddDirectableEnemy(GameObjectHandle enemy)
{
	enemies_.push_back(enemy);
}

GameObjectHandle MainScene::GetNearestEnemy()
{
	return nearest_enemy_;
}

void MainScene::AddMyself()
{
	myself_handle_ = AddObject(MatVec::Vector2(0, -275), 1.0, 0.0);
	//���̃R���|�[�l���g�̂�MainScene���m���Ă����Ȃ���΂Ȃ�Ȃ��̂ł����Œǉ�
	myself_pos_angle_handle_ = myself_handle_->AddUpdateComponent<MyselfPosAndAngleComponent>(myself_handle_, this);
	//���̃R���|�[�l���g�̒ǉ��̓��f�B�G�[�^�ɔC����
	myself_handle_->AddUpdateComponent<MyselfMediatorComponent>(myself_handle_,this);
}

void MainScene::FindNearestEnemy()
{
	//���@�̈ʒu
	MatVec::Vector2 myself = myself_handle_->GetPosition();
	//���܂łɌ����G�@�̒��ŁC���@�ƍł��߂����̂́C���@�Ƃ̋������
	double mind2 = 1e9;
	//�����ŏ��ƂȂ�G�@
	nearest_enemy_ = GameObjectHandle();
	auto itr = enemies_.begin();
	//����ł�����̃`�F�b�N�������ɍs��
	while (itr != enemies_.begin())
	{
		if (!(*itr).IsValid())
		{
			itr = enemies_.erase(itr);
		}
		else {
			MatVec::Vector2 pos = (*itr)->GetPosition();
			pos -= myself;
			double d2 = pos(0) * pos(0) + pos(1) * pos(1);
			if (mind2 > d2)
			{
				mind2 = d2;
				nearest_enemy_ = *itr;
			}
		}
	}

}

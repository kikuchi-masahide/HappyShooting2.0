#include "MainScene.h"

#include "MainSceneBasicLayer.h"
#include "MainSceneUIScreen.h"
#include "DrawTextureComponent.h"
#include "MyselfPosAndAngleComponent.h"
#include "MyselfMediatorComponent.h"
#include "DrawNormalBulletComponent.h"

MainScene::MainScene(Game* game)
	:Scene(game),layer_from_next_tick_(999)
{
	//自機追加
	AddMyself();

	//レイヤー
	auto layer0 = AddLayer<MainSceneBasicLayer>(this,myself_pos_angle_handle_);
	available_layers_[0] = static_cast<LayerHandle<MainSceneBaseLayer>>(layer0);
	//始めはレイヤー0を有効化
	active_layer_ = available_layers_[0];
	active_layer_->SetActive();

	//UIScreen
	AddUIScreen<MainSceneUIScreen>(this);
}

void MainScene::UniqueUpdate()
{
	//レイヤーの入れ替え
	if (layer_from_next_tick_ != 999)
	{
		active_layer_->SetUnActive();
		active_layer_ = available_layers_[layer_from_next_tick_];
		active_layer_->SetActive();
		layer_from_next_tick_ = 999;
	}
}

void MainScene::UniqueOutput()
{
	FindNearestEnemy();
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
	//このコンポーネントのみMainSceneが知っておかなければならないのでここで追加
	myself_pos_angle_handle_ = myself_handle_->AddUpdateComponent<MyselfPosAndAngleComponent>(myself_handle_, this);
	//他のコンポーネントの追加はメディエータに任せる
	myself_handle_->AddUpdateComponent<MyselfMediatorComponent>(myself_handle_,this);
}

void MainScene::FindNearestEnemy()
{
	//自機の位置
	MatVec::Vector2 myself = myself_handle_->GetPosition();
	//今までに見た敵機の中で，自機と最も近いものの，自機との距離二乗
	double mind2 = 1e9;
	//距離最小となる敵機
	nearest_enemy_ = GameObjectHandle();
	auto itr = enemies_.begin();
	//死んでいるものチェックも同時に行う
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

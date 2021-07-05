#include "MainScene.h"

#include "MainSceneBasicLayer.h"
#include "MainSceneUIScreen.h"
#include "DrawTextureComponent.h"
#include "MyselfPosAndAngleComponent.h"
#include "MyselfMediatorComponent.h"
#include "DrawNormalBulletComponent.h"
#include "MyselfAddNormalBulletComponent.h"
#include "TestCollisionComponent.h"

MainScene::MainScene(Game* game)
	:Scene(game),layer_from_next_tick_(999)
{
	//自機追加
	AddMyself();

	//テスト用に当たり判定領域を追加
	MatVec::Vector2 position[4];
	position[0] = MatVec::Vector2(-150, +150);
	position[1] = MatVec::Vector2(-150, -150);
	position[2] = MatVec::Vector2(+150, -150);
	position[3] = MatVec::Vector2(+150, +150);
	for (unsigned int n = 0; n < 4; n++)
	{
		auto obj = AddObject(position[n], 1.0, 0.0);
		obj->AddOutputComponent<DrawNormalBulletComponent>(this, obj, 80, MatVec::Vector3(0.0, 1.0, 0.0),1.0);
		obj->AddUpdateComponent<TestCollisionComponent>(n, obj, 80, false, this);
	}

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
	//当たり判定トラバースの実行
	collision_manager_.TraverseAll();
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

void MainScene::AddMyself()
{
	myself_handle_ = AddObject(MatVec::Vector2(0, -275), 1.0, 0.0);
	auto draw_texture_component = myself_handle_->AddOutputComponent<DrawTextureComponent>(this, 4, myself_handle_);
	draw_texture_component->width_ = 40;
	draw_texture_component->height_ = 40;
	myself_pos_angle_handle_ = myself_handle_->AddUpdateComponent<MyselfPosAndAngleComponent>(myself_handle_, this);
	myself_handle_->AddUpdateComponent<MyselfMediatorComponent>(draw_texture_component);
	myself_handle_->AddUpdateComponent<MyselfAddNormalBulletComponent>(myself_handle_, this);

	//test
	myself_handle_->AddUpdateComponent<TestCollisionComponent>(4, myself_handle_, 1, false, this);
}

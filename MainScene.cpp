#include "MainScene.h"

#include "MainSceneBasicLayer.h"

MainScene::MainScene(Game* game)
	:Scene(game),layer_from_next_tick_(999)
{
	//���C���[
	auto layer0 = AddLayer<MainSceneBasicLayer>();
	available_layers_[0] = static_cast<LayerHandle<MainSceneBaseLayer>>(layer0);
	//�n�߂̓��C���[0��L����
	active_layer_ = available_layers_[0];
	active_layer_->SetActive();
}

void MainScene::UniqueUpdate()
{
	//���C���[�̓���ւ�
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

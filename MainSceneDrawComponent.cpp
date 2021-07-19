#include "MainSceneDrawComponent.h"

#include "MainScene.h"

MainSceneDrawComponent::MainSceneDrawComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager)
	:Component(object, 0), layer_manager_(layer_manager)
{
}

void MainSceneDrawComponent::Update()
{
	layer_manager_->AddComponentToLayer(This<MainSceneDrawComponent>());
}

MainSceneDrawComponent::~MainSceneDrawComponent()
{
}

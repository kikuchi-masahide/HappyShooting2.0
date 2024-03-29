#include "MainSceneDrawComponent.h"

#include "MainScene.h"

MainSceneDrawComponent::MainSceneDrawComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager,double z)
	:Component(object, 0), layer_manager_(layer_manager),z_(z)
{
	layer_manager_->AddComponentToLayer(This<MainSceneDrawComponent>());
}

void MainSceneDrawComponent::Update()
{
}

MainSceneDrawComponent::~MainSceneDrawComponent()
{
}

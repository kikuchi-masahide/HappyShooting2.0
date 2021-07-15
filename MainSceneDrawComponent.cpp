#include "MainSceneDrawComponent.h"

#include "MainScene.h"

MainSceneDrawComponent::MainSceneDrawComponent(GameObjectHandle object, MainScene* scene)
	:Component(object, 0),scene_(scene)
{
}

void MainSceneDrawComponent::Update()
{
	scene_->AddComponentToLayer(This<MainSceneDrawComponent>());
}

MainSceneDrawComponent::~MainSceneDrawComponent()
{
}

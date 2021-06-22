#include "MainSceneDrawComponent.h"

#include "MainScene.h"

MainSceneDrawComponent::MainSceneDrawComponent(MainScene* scene)
	:Component(0),scene_(scene)
{
}

void MainSceneDrawComponent::Update()
{
	scene_->AddComponentToLayer(This<MainSceneDrawComponent>());
}

MainSceneDrawComponent::~MainSceneDrawComponent()
{
}

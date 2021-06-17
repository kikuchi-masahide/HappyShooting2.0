#include "MainSceneDrawComponent.h"

#include "MainScene.h"

MainSceneDrawComponent::MainSceneDrawComponent(GameObject* owner, boost::shared_ptr<std::set<void*>> hset, MainScene* scene)
	:Component(owner,hset,0),scene_(scene)
{
}

void MainSceneDrawComponent::Update()
{
	scene_->AddComponentToLayer(This<MainSceneDrawComponent>());
}

MainSceneDrawComponent::~MainSceneDrawComponent()
{
}

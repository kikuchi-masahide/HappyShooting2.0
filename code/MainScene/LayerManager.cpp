#include "LayerManager.h"

#include "MainSceneBasicLayer.h"
#include "../Engine/Scene.h"

LayerManager::LayerManager(Scene* scene)
	:layer_from_next_tick_(999),scene_(scene)
{
	auto layer0 = scene->AddLayer<MainSceneBasicLayer>(scene);
	available_layers_[0] = static_cast<LayerHandle<MainSceneBaseLayer>>(layer0);
	//始めはレイヤー0を有効化
	active_layer_ = available_layers_[0];
	active_layer_->SetActive();
}

LayerManager::~LayerManager()
{
}

void LayerManager::AddComponentToLayer(ComponentHandle<MainSceneDrawComponent> component)
{
	active_layer_->AddComponent(component);
}

void LayerManager::SwapLayer(unsigned int ind)
{
	layer_from_next_tick_ = ind;
}

MatVec::Matrix4x4 LayerManager::GetLayerTransform()
{
	return active_layer_->GetLayerTransform();
}

void LayerManager::PriorUniqueUpdate()
{
	if (layer_from_next_tick_ != 999)
	{
		active_layer_->SetUnActive();
		active_layer_ = available_layers_[layer_from_next_tick_];
		active_layer_->SetActive();
		layer_from_next_tick_ = 999;
	}
}

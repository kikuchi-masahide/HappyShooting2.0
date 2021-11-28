#include "LayerManager.h"

#include "MainSceneBasicLayer.h"
#include "MainSceneClippingLayer.h"
#include "../Engine/Scene.h"
#include "MainSceneDrawComponent.h"
#include "MainSceneShrinkLayer.h"

LayerManager::LayerManager(Scene* scene)
	:layer_from_next_tick_(999),scene_(scene)
{
}

LayerManager::~LayerManager()
{
}

void LayerManager::InitLayers()
{
	auto layer0 = scene_->AddLayer<MainSceneBasicLayer>(scene_,&draw_components_);
	available_layers_[0] = static_cast<LayerHandle<MainSceneBaseLayer>>(layer0);
	//始めはレイヤー0を有効化
	active_layer_ = available_layers_[0];
	active_layer_->SetActive();

	auto layer1 = scene_->AddLayer<MainSceneClippingLayer>(scene_,&draw_components_, myself_);
	available_layers_[1] = static_cast<LayerHandle<MainSceneBaseLayer>>(layer1);

	auto layer2 = scene_->AddLayer<MainSceneShrinkLayer>(scene_, &draw_components_);
	available_layers_[2] = static_cast<LayerHandle<MainSceneBaseLayer>>(layer2);
}

void LayerManager::AddComponentToLayer(ComponentHandle<MainSceneDrawComponent> component)
{
	draw_components_.emplace(component);
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

void LayerManager::SetMyselfHandle(GameObjectHandle handle)
{
	myself_ = handle;
}

DrawComponentUnit::DrawComponentUnit(ComponentHandle<MainSceneDrawComponent> comp)
	:comp_(comp),z_(comp->z_)
{
}

bool DrawComponentCompare::operator()(const DrawComponentUnit& left, const DrawComponentUnit& right) const
{
	return left.z_ < right.z_;
}

#include "stdafx.h"
#include "DrawTextureComponent.h"

#include "MainScene.h"
#include "GameObject.h"

DrawTextureComponent::DrawTextureComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, unsigned int texture_id)
	:MainSceneDrawComponent(object, layer_manager),
	draw_helper_(layer_manager->scene_->mGame, texture_id),
	center_offset_(),angle_offset_(0),alpha_(1.0),width_(0.0),height_(0.0)
{
}

DrawTextureComponent::~DrawTextureComponent()
{
}

void DrawTextureComponent::Draw()
{
	auto center = mObj->GetPosition()+center_offset_;
	auto angle = mObj->GetRotation() + angle_offset_;
	draw_helper_.Draw(layer_manager_->scene_->mGame, center(0), center(1), width_, height_, angle, alpha_, 600, 900);
}

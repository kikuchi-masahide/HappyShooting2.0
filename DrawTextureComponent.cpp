#include "stdafx.h"
#include "DrawTextureComponent.h"

#include "MainScene.h"
#include "GameObject.h"

DrawTextureComponent::DrawTextureComponent(MainScene* scene, unsigned int texture_id, GameObjectHandle object)
	:MainSceneDrawComponent(scene),
	draw_helper_(scene->mGame, texture_id), object_(object),
	center_offset_(),angle_offset_(0),alpha_(1.0),width_(0.0),height_(0.0)
{
}

DrawTextureComponent::~DrawTextureComponent()
{
}

void DrawTextureComponent::Draw()
{
	auto center = object_->GetPosition()+center_offset_;
	auto angle = object_->GetRotation() + angle_offset_;
	//draw_helper_.Draw(scene_->mGame, center(0), center(1), width_, height_, angle, alpha_, 600, 900);
}

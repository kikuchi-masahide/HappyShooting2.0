#include "stdafx.h"
#include "MyselfMediatorComponent.h"

#include "DrawTextureComponent.h"
#include "MainScene.h"
#include "MyselfAddNormalBulletComponent.h"
#include "MyselfCollisionComponent.h"

MyselfMediatorComponent::MyselfMediatorComponent(GameObjectHandle myself, MainScene* scene)
	:Component(myself, 50),damage_counter_(-1),scene_(scene)
{
	draw_texture_component_ = myself->AddOutputComponent<DrawTextureComponent>(scene->GetLayerManager(), 4);
	draw_texture_component_->width_ = 40;
	draw_texture_component_->height_ = 40;
	mObj->AddUpdateComponent<MyselfAddNormalBulletComponent>(scene_);
	mObj->AddUpdateComponent<MyselfCollisionComponent>(scene_, This<MyselfMediatorComponent>());
}

void MyselfMediatorComponent::Update()
{
}

void MyselfMediatorComponent::CauseDamageToMyself(unsigned int point)
{
	damage_counter_ = 120;
	scene_->AddScore(-1000);
}

MyselfMediatorComponent::~MyselfMediatorComponent()
{
}

void MyselfMediatorComponent::SetMyselfAlpha()
{
	//�ʏ펞
	if (damage_counter_ == -1)
	{
		draw_texture_component_->alpha_ = 1.0;
	}
	else
	{
		double theta = 2 * PI * damage_counter_ / 60;
		draw_texture_component_->alpha_ = 1 - cos(theta);
		if (draw_texture_component_->alpha_ > 1.0)
		{
			draw_texture_component_->alpha_ = 1.0;
		}
		damage_counter_--;
	}
}

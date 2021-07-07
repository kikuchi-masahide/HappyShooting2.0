#include "stdafx.h"
#include "MyselfMediatorComponent.h"

#include "DrawTextureComponent.h"
#include "MainScene.h"

MyselfMediatorComponent::MyselfMediatorComponent(ComponentHandle<DrawTextureComponent> draw_texture_component, MainScene* scene)
	:Component(50),draw_texture_component_(draw_texture_component),damage_counter_(-1),scene_(scene)
{
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

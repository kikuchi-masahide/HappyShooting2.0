#include "stdafx.h"
#include "MyselfMediatorComponent.h"

MyselfMediatorComponent::MyselfMediatorComponent(ComponentHandle<DrawTextureComponent> draw_texture_component)
	:Component(50),draw_texture_component_(draw_texture_component)
{
}

void MyselfMediatorComponent::Update()
{
}

MyselfMediatorComponent::~MyselfMediatorComponent()
{
}

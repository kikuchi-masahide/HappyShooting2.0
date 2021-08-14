#include "stdafx.h"
#include "MyselfPosAndAngleComponent.h"

#include "MainScene.h"
#include "GameObject.h"
#include "LayerManager.h"

MyselfPosAndAngleComponent::MyselfPosAndAngleComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer_manager)
	:Component(handle, 100),
	layer_manager_(layer_manager)
{
}

void MyselfPosAndAngleComponent::Update()
{
	//ˆÚ“®Œã‚ÌÀ•W‚ð‹‚ß‚é
	auto after_pos = mObj->GetPosition();
	auto scene = mObj->mScene;
	if (scene->GetKeyState('A') == ButtonState::Pressed ||
		scene->GetKeyState('A') == ButtonState::Held)
	{
		after_pos(0) -= moving_dist_;
	}
	if (scene->GetKeyState('D') == ButtonState::Pressed ||
		scene->GetKeyState('D') == ButtonState::Held)
	{
		after_pos(0) += moving_dist_;
	}
	if (scene->GetKeyState('W') == ButtonState::Pressed ||
		scene->GetKeyState('W') == ButtonState::Held)
	{
		after_pos(1) += moving_dist_;
	}
	if (scene->GetKeyState('S') == ButtonState::Pressed ||
		scene->GetKeyState('S') == ButtonState::Held)
	{
		after_pos(1) -= moving_dist_;
	}
	//‰æ–Ê“à‚É‚Æ‚Ç‚Ü‚ç‚¹‚é
	after_pos(0) = Max(after_pos(0), -300.0);
	after_pos(0) = Min(after_pos(0), 300.0);
	after_pos(1) = Max(after_pos(1), -450.0);
	after_pos(1) = Min(after_pos(1), 450.0);
	mObj->SetPosition(after_pos);
}

MyselfPosAndAngleComponent::~MyselfPosAndAngleComponent()
{
}

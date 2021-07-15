#include "stdafx.h"
#include "MyselfPosAndAngleComponent.h"

#include "MainScene.h"
#include "GameObject.h"

MyselfPosAndAngleComponent::MyselfPosAndAngleComponent(GameObjectHandle handle, MainScene* scene)
	:Component(handle, 100),
	layer_transform_(MatVec::Identity4x4()),main_scene_(scene)
{
}

void MyselfPosAndAngleComponent::Update()
{
	//移動後の座標を求める
	auto after_pos = mObj->GetPosition();
	if (main_scene_->GetKeyState('A') == ButtonState::Pressed ||
		main_scene_->GetKeyState('A') == ButtonState::Held)
	{
		after_pos(0) -= moving_dist_;
	}
	if (main_scene_->GetKeyState('D') == ButtonState::Pressed ||
		main_scene_->GetKeyState('D') == ButtonState::Held)
	{
		after_pos(0) += moving_dist_;
	}
	if (main_scene_->GetKeyState('W') == ButtonState::Pressed ||
		main_scene_->GetKeyState('W') == ButtonState::Held)
	{
		after_pos(1) += moving_dist_;
	}
	if (main_scene_->GetKeyState('S') == ButtonState::Pressed ||
		main_scene_->GetKeyState('S') == ButtonState::Held)
	{
		after_pos(1) -= moving_dist_;
	}
	//画面内にとどまらせる
	after_pos(0) = Max(after_pos(0), -300.0);
	after_pos(0) = Min(after_pos(0), 300.0);
	after_pos(1) = Max(after_pos(1), -450.0);
	after_pos(1) = Min(after_pos(1), 450.0);
	mObj->SetPosition(after_pos);

	//自機に変形layer_transform_をかけた後カーソル位置を向いているようにしたい
	//LU分解でlayer_transform_の逆行列を求める
	MatVec::Matrix4x4 layer_transform_inv = MatVec::GetInverseMatrix(layer_transform_);
	//カーソル位置を，(300,450)を中心とする左手系座標に変換
	auto cursor_pos_xy = main_scene_->GetMouseClientPos(0);
	cursor_pos_xy -= MatVec::Vector2(300.0, 450.0);
	auto cursor_pos_xyzw = MatVec::Vector4(cursor_pos_xy(0), cursor_pos_xy(1), 0.0, 1.0);
	//カーソル位置を，レイヤー変形前の位置に変換
	cursor_pos_xyzw = layer_transform_inv * cursor_pos_xyzw;
	MatVec::Vector2 cursor_pos_before(
		cursor_pos_xyzw(0)/ cursor_pos_xyzw(3), cursor_pos_xyzw(1)/cursor_pos_xyzw(3)
	);
	auto myself_pos = mObj->GetPosition();
	//角度をセット
	mObj->SetRotation(std::atan2(
		cursor_pos_before(1) - myself_pos(1), cursor_pos_before(0) - myself_pos(0)
	));
}

MyselfPosAndAngleComponent::~MyselfPosAndAngleComponent()
{
}

void MyselfPosAndAngleComponent::SetLayerTransform(MatVec::Matrix4x4 matrix)
{
	layer_transform_ = matrix;
}

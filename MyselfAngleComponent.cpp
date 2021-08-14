#include "stdafx.h"
#include "MyselfAngleComponent.h"

#include "LayerManager.h"
#include "Scene.h"

MyselfAngleComponent::MyselfAngleComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer_manager)
	:Component(handle,90),
	layer_manager_(layer_manager)
{
	scene_ = mObj->mScene;
}

MyselfAngleComponent::~MyselfAngleComponent()
{
}

void MyselfAngleComponent::Update()
{
	//自機に変形layer_transform_をかけた後カーソル位置を向いているようにしたい
	//LU分解でlayer_transform_の逆行列を求める
	MatVec::Matrix4x4 layer_transform_ = layer_manager_->GetLayerTransform();
	MatVec::Matrix4x4 layer_transform_inv = MatVec::GetInverseMatrix(layer_transform_);
	//カーソル位置を，(300,450)を中心とする左手系座標に変換
	auto cursor_pos_xy = scene_->GetMouseClientPos(0);
	cursor_pos_xy -= MatVec::Vector2(300.0, 450.0);
	auto cursor_pos_xyzw = MatVec::Vector4(cursor_pos_xy(0), cursor_pos_xy(1), 0.0, 1.0);
	//カーソル位置を，レイヤー変形前の位置に変換
	cursor_pos_xyzw = layer_transform_inv * cursor_pos_xyzw;
	MatVec::Vector2 cursor_pos_before(
		cursor_pos_xyzw(0) / cursor_pos_xyzw(3), cursor_pos_xyzw(1) / cursor_pos_xyzw(3)
	);
	auto myself_pos = mObj->GetPosition();
	//角度をセット
	mObj->SetRotation(std::atan2(
		cursor_pos_before(1) - myself_pos(1), cursor_pos_before(0) - myself_pos(0)
	));
}

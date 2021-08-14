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
	//���@�ɕό`layer_transform_����������J�[�\���ʒu�������Ă���悤�ɂ�����
	//LU������layer_transform_�̋t�s������߂�
	MatVec::Matrix4x4 layer_transform_ = layer_manager_->GetLayerTransform();
	MatVec::Matrix4x4 layer_transform_inv = MatVec::GetInverseMatrix(layer_transform_);
	//�J�[�\���ʒu���C(300,450)�𒆐S�Ƃ��鍶��n���W�ɕϊ�
	auto cursor_pos_xy = scene_->GetMouseClientPos(0);
	cursor_pos_xy -= MatVec::Vector2(300.0, 450.0);
	auto cursor_pos_xyzw = MatVec::Vector4(cursor_pos_xy(0), cursor_pos_xy(1), 0.0, 1.0);
	//�J�[�\���ʒu���C���C���[�ό`�O�̈ʒu�ɕϊ�
	cursor_pos_xyzw = layer_transform_inv * cursor_pos_xyzw;
	MatVec::Vector2 cursor_pos_before(
		cursor_pos_xyzw(0) / cursor_pos_xyzw(3), cursor_pos_xyzw(1) / cursor_pos_xyzw(3)
	);
	auto myself_pos = mObj->GetPosition();
	//�p�x���Z�b�g
	mObj->SetRotation(std::atan2(
		cursor_pos_before(1) - myself_pos(1), cursor_pos_before(0) - myself_pos(0)
	));
}

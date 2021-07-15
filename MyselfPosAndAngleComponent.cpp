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
	//�ړ���̍��W�����߂�
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
	//��ʓ��ɂƂǂ܂点��
	after_pos(0) = Max(after_pos(0), -300.0);
	after_pos(0) = Min(after_pos(0), 300.0);
	after_pos(1) = Max(after_pos(1), -450.0);
	after_pos(1) = Min(after_pos(1), 450.0);
	mObj->SetPosition(after_pos);

	//���@�ɕό`layer_transform_����������J�[�\���ʒu�������Ă���悤�ɂ�����
	//LU������layer_transform_�̋t�s������߂�
	MatVec::Matrix4x4 layer_transform_inv = MatVec::GetInverseMatrix(layer_transform_);
	//�J�[�\���ʒu���C(300,450)�𒆐S�Ƃ��鍶��n���W�ɕϊ�
	auto cursor_pos_xy = main_scene_->GetMouseClientPos(0);
	cursor_pos_xy -= MatVec::Vector2(300.0, 450.0);
	auto cursor_pos_xyzw = MatVec::Vector4(cursor_pos_xy(0), cursor_pos_xy(1), 0.0, 1.0);
	//�J�[�\���ʒu���C���C���[�ό`�O�̈ʒu�ɕϊ�
	cursor_pos_xyzw = layer_transform_inv * cursor_pos_xyzw;
	MatVec::Vector2 cursor_pos_before(
		cursor_pos_xyzw(0)/ cursor_pos_xyzw(3), cursor_pos_xyzw(1)/cursor_pos_xyzw(3)
	);
	auto myself_pos = mObj->GetPosition();
	//�p�x���Z�b�g
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

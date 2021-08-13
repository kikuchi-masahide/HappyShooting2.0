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
	//�ړ���̍��W�����߂�
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
	//��ʓ��ɂƂǂ܂点��
	after_pos(0) = Max(after_pos(0), -300.0);
	after_pos(0) = Min(after_pos(0), 300.0);
	after_pos(1) = Max(after_pos(1), -450.0);
	after_pos(1) = Min(after_pos(1), 450.0);
	mObj->SetPosition(after_pos);

	//���@�ɕό`layer_transform_����������J�[�\���ʒu�������Ă���悤�ɂ�����
	//LU������layer_transform_�̋t�s������߂�
	MatVec::Matrix4x4 layer_transform_ = layer_manager_->GetLayerTransform();
	MatVec::Matrix4x4 layer_transform_inv = MatVec::GetInverseMatrix(layer_transform_);
	//�J�[�\���ʒu���C(300,450)�𒆐S�Ƃ��鍶��n���W�ɕϊ�
	auto cursor_pos_xy = scene->GetMouseClientPos(0);
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

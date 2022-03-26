#include "MyBulletComponent.h"

#include "../Engine/GameObject.h"
#include "MyBulletCollisionComponent.h"
#include "DrawNormalBulletComponent.h"

MyBulletComponent::MyBulletComponent(GameObjectHandle obj, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col, MatVec::Vector2 d, double radius)
	:Component(obj),
	d_(d),radius_(radius),last_time_in_stage_(-1), speed_(1),time_(-1)
{
	collision_= mObj->AddUpdateComponent<MyBulletCollisionComponent>(col, 100, radius_);
	draw_ = mObj->AddOutputComponent<DrawNormalBulletComponent>(
		layer, radius_, MatVec::Vector3(0.0, 0.0, 1.0), 1.0, 10.0);
}

MyBulletComponent::~MyBulletComponent()
{
}

void MyBulletComponent::Update()
{
	time_ += speed_;
	auto pos = mObj->GetPosition() + d_*speed_;
	mObj->SetPosition(pos);
	//���s�Đ��̏ꍇ
	if (speed_ == 1)
	{
		//��ʓ��A�����ɂ��������ĂȂ��Ȃ��
		if (abs(pos(0)) <= 300.0 + radius_ && abs(pos(1)) <= 450.0 + radius_ && collision_->active_)
		{
			last_time_in_stage_ = max(last_time_in_stage_, time_);
			draw_->edge_alpha_ = 1.0;
		}
		else {
			collision_->active_ = false;
			draw_->edge_alpha_ = 0.0;
		}
		//�Ō�ɓo�ꂵ�Ă��玞�Ԃ��o����������E��
		if (time_ >= last_time_in_stage_ + grace_time_)
		{
			mObj->SetDeleteFlag();
		}
	}
	//�t�s�Đ��̏ꍇ
	else {
		//���s�Đ��̎��A����time_�ł͕`��E�����蔻�肪�����Ă���
		if (time_ <= last_time_in_stage_)
		{
			draw_->edge_alpha_ = 1.0;
			last_time_in_stage_ = time_;
		}
		else {
			draw_->edge_alpha_ = 0.0;
		}
	}
	//���Ő��܂ꂽ�O�ɖ߂肻���Ȃ̂ŎE��
	if (time_ + speed_ < 0)
	{
		mObj->SetDeleteFlag();
	}
}

void MyBulletComponent::SetProgradePlay()
{
	speed_ = 1;
	//�t�s�Đ��̖��A���肪�����Ă������܂Ŗ߂���
	if (time_ <= last_time_in_stage_)
	{
		collision_->active_ = true;
	}
}

void MyBulletComponent::SetRetrogradePlay(unsigned int speed)
{
	if (speed != 0)
	{
		speed_ = -(int)(speed);
		//�t�s�Đ����͓����蔻���؂�
		collision_->active_ = false;
	}
}

void MyBulletComponent::NoticeCollision()
{
	//�Փ˔�����s��Ȃ�����
	collision_->active_ = true;
}

const int MyBulletComponent::grace_time_ = 480;

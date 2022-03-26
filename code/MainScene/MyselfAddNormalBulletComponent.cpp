#include "MyselfAddNormalBulletComponent.h"

#include "../Engine/Game.h"
#include "../Engine/Scene.h"
#include "MyBulletComponent.h"
#include "DrawNormalBulletComponent.h"
#include "MyBulletCollisionComponent.h"

MyselfAddNormalBulletComponent::MyselfAddNormalBulletComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<CollisionManager> collision_manager)
	:Component(handle, 30),
	time_(0),layer_manager_(layer_manager),collision_manager_(collision_manager),is_active_(true),speed_(1)
{
}

MyselfAddNormalBulletComponent::~MyselfAddNormalBulletComponent()
{
}

void MyselfAddNormalBulletComponent::Update()
{
	if (time_ % period_to_fire_ == 0)
	{
		//�e���猂���Ă����ƌ����Ă��āA�����s�Đ����̎�
		if (is_active_ && speed_ == 1) {
			double angle = mObj->GetRotation();
			auto pos = mObj->GetPosition();
			//TODO:Enemy7(�o���A�����Ă���)�̂��߂ɁA�u�e�I�u�W�F�N�g��rotation�����ł������ł���v��
			//�������ƂɂƂ肠�������Ă�
			//����������Ƃ��������Ȃ�?�����蔻��܂킢����ς��Ȃ��Ƃ���?(�e���v���[�g���ꉻ���g���Ȃ�)
			GameObjectHandle bullet = mObj->mScene->AddObject(pos, 1.0, angle);
			auto dist = MatVec::Vector2(cos(angle) * moving_dist_, sin(angle) * moving_dist_);
			auto move = bullet->AddUpdateComponent<MyBulletComponent>(
				layer_manager_,collision_manager_,dist,bullet_redius_
				);
			bullets_.push_back(move);
		}
		time_ = 0;
		//����ł��̃`�F�b�N
		for (auto itr = bullets_.begin(); itr != bullets_.end();)
		{
			if (!itr->IsValid())
			{
				itr = bullets_.erase(itr);
			}
			else {
				itr++;
			}
		}
	}
	time_ += speed_;
}

void MyselfAddNormalBulletComponent::SetProgradePlay()
{
	speed_ = 1;
	for (auto& comp : bullets_)
	{
		if (comp.IsValid()) {
			comp->SetProgradePlay();
		}
	}
}

void MyselfAddNormalBulletComponent::SetRetrogradePlay(unsigned int speed)
{
	if (speed != 0) {
		speed_ = -(int)(speed);
		for (auto& comp : bullets_)
		{
			if (comp.IsValid()) {
				comp->SetRetrogradePlay(speed);
			}
		}
	}
}


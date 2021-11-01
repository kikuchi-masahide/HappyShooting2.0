#include "MyselfCollisionComponent.h"

#include "MyselfMediatorComponent.h"
#include "../Engine/GameObject.h"

#include "MainScene.h"

MyselfCollisionComponent::MyselfCollisionComponent(GameObjectHandle myself, boost::shared_ptr<CollisionManager> manager, ComponentHandle<MyselfMediatorComponent> mediator)
	:CollisionComponent(myself, manager, 75,CollisionManager::Tag::Myself,damage_),
	geometry_(This<CollisionComponent>(), myself->GetPosition(),circle_radius_),mediator_(mediator)
{
}

MyselfCollisionComponent::~MyselfCollisionComponent()
{
}

void MyselfCollisionComponent::Update()
{
	//�~�̈ʒu�X�V
	geometry_.center_ = mObj->GetPosition();
	manager_->AddFriendlyGeometry(&geometry_);
}

void MyselfCollisionComponent::CheckHitComponent()
{
	if (hit_comps_.size() == 0)return;
	//���@���_���[�W������Ȃ���ԂȂ�΁C�e�ɓ������Ă��Ă����Ȃ�
	if (mediator_->IsInvincible())return;
	//�n�߂̈ꌂ�݂̂����Ă���
	auto comp = *(hit_comps_.begin());
	//�G�@�܂��̓��[�U�[�Ɠ��������ꍇ
	if (comp->tag_ == CollisionManager::Tag::EnemyBody || comp->tag_ == CollisionManager::Tag::EnemyLazer)
	{
		mediator_->CauseDamageToMyself(comp->GetDamage());
	}
	//�G�e�Ɠ��������ꍇ
	if (comp->tag_ == CollisionManager::Tag::EnemyBullet)
	{
		mediator_->CauseDamageToMyself(comp->GetDamage());
		comp->mObj->SetDeleteFlag();
	}
}
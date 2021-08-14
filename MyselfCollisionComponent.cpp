#include "stdafx.h"
#include "MyselfCollisionComponent.h"

#include "MyselfMediatorComponent.h"
#include "GameObject.h"

#include "MainScene.h"

MyselfCollisionComponent::MyselfCollisionComponent(GameObjectHandle myself, boost::shared_ptr<CollisionManager> manager, ComponentHandle<MyselfMediatorComponent> mediator)
	:CollisionComponent(myself, manager, 75,myself_tag_,damage_),
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
	manager_->AddCircleGeometry(geometry_);
}

void MyselfCollisionComponent::CheckHitComponent()
{
	if (hit_comps_.size() == 0)return;
	//���@���_���[�W������Ȃ���ԂȂ�΁C�e�ɓ������Ă��Ă����Ȃ�
	if (mediator_->IsInvincible())return;
	//�n�߂̈ꌂ�݂̂����Ă���
	auto comp = *(hit_comps_.begin());
	if (comp->tag_ == 2)
	{
		mediator_->CauseDamageToMyself(comp->GetDamage());
		comp->SetDeleteFlag();
	}
}

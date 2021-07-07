#include "stdafx.h"
#include "MyselfCollisionComponent.h"

#include "MyselfMediatorComponent.h"
#include "GameObject.h"

#include "MainScene.h"

MyselfCollisionComponent::MyselfCollisionComponent(MainScene* scene, GameObjectHandle myself, ComponentHandle<MyselfMediatorComponent> mediator)
	:CollisionComponent(75,myself_tag_,damage_),
	/*collision_manager_(collision_manager)*/scene_(scene),geometry_(This<CollisionComponent>(),
	myself->GetPosition(),circle_radius_),myself_(myself),mediator_(mediator)
{
}

MyselfCollisionComponent::~MyselfCollisionComponent()
{
}

void MyselfCollisionComponent::Update()
{
	//�ꔭ�ł��������Ă�����_���[�W����炤
	if (hit_comps_.size() > 0)
	{
		mediator_->CauseDamageToMyself(hit_comps_[0]->GetDamage());
	}
	hit_comps_.clear();

	//�~�̈ʒu�X�V
	geometry_.center_ = myself_->GetPosition();
	scene_->collision_myself_.AddCollisionComponent(This<CollisionComponent>());
}

void MyselfCollisionComponent::AddGeometryToManager(CollisionManager& manager)
{
	manager.circles_.push_back(geometry_);
}

#include "stdafx.h"
#include "TestCollisionComponent.h"

#include "MainScene.h"

TestCollisionComponent::TestCollisionComponent(unsigned int tag, GameObjectHandle obj, double radius, bool delete_flag, MainScene* scene)
	:CollisionComponent(0,tag,0),
	circle_(This<CollisionComponent>(),obj->GetPosition(),radius),obj_(obj),delete_flag_(delete_flag),scene_(scene)
{
}

TestCollisionComponent::~TestCollisionComponent()
{
}

void TestCollisionComponent::Update()
{
	bool did_hit_ = false;
	for (auto comp : hit_comps_)
	{
		if (!comp.IsValid())continue;
		std::string message("TestCollisionComponent ");
		message += std::to_string(tag_);
		message += " hits with TestCollisionComponent";
		message += std::to_string(comp->tag_);
		//Log::OutputTrivial(message);
		did_hit_ = true;
	}
	if (did_hit_ && delete_flag_)
	{
		obj_->SetDeleteFlag();
	}
	else {
		scene_->collision_manager_.AddCollisionComponent(This<CollisionComponent>());
	}

}

void TestCollisionComponent::AddGeometryToManager(CollisionManager& manager)
{
	circle_.center_ = obj_->GetPosition();
	manager.circles_.push_back(circle_);
}

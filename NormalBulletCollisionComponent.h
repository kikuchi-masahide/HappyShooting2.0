#pragma once
#include "CollisionComponent.h"

class CollisionManager;

class NormalBulletCollisionComponent
	:public CollisionComponent
{
public:
	NormalBulletCollisionComponent(GameObjectHandle obj, double radius,unsigned int damage,boost::shared_ptr<CollisionManager> collision_manager);
	~NormalBulletCollisionComponent();
	void Update() override;
	void CheckHitComponent() override;
private:
	CircleGeometry circle_;
};


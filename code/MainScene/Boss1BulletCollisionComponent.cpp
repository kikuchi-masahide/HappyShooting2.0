#include "Boss1BulletCollisionComponent.h"

#include "../Engine/GameObject.h"

Boss1BulletCollisionComponent::Boss1BulletCollisionComponent(GameObjectHandle obj, boost::shared_ptr<CollisionManager> collision_manager)
	:CollisionComponent(obj, collision_manager,100,CollisionManager::Tag::EnemyBullet,100),
	polygon_(This<CollisionComponent>(),4),template_(ComponentHandle<CollisionComponent>(),4)
{
	double deg = obj->GetRotation();
	MatVec::Vector4 p[4];
	p[0] = MatVec::XYZ1(MatVec::Vector3(10.0, 0.0,0.0));
	p[1] = MatVec::XYZ1(MatVec::Vector3(-10.0, +10.0 * 11 / 15, 0.0));
	p[2] = MatVec::XYZ1(MatVec::Vector3(-5.0, 0.0, 0.0));
	p[3] = MatVec::XYZ1(MatVec::Vector3(-10.0, -10.0 * 11 / 15, 0.0));
	MatVec::Matrix4x4 rotate = MatVec::Rotate(MatVec::GetQuaternion(MatVec::Vector3(0.0, 0.0, -1.0), deg));
	for (int n = 0; n < 4; n++)
	{
		p[n] = rotate * p[n];
		template_.points_[n] = MatVec::Vector2(p[n](0) / p[n](3), p[n](1) / p[n](3));
	}
}

Boss1BulletCollisionComponent::~Boss1BulletCollisionComponent()
{
}

void Boss1BulletCollisionComponent::Update()
{
	MatVec::Vector2 objpos(mObj->GetPosition()(0), mObj->GetPosition()(1));
	for (int n = 0; n < 4; n++) {
		polygon_.points_[n] = template_.points_[n] + objpos;
	}
	manager_->AddEnemyGeometry(&polygon_);
}

void Boss1BulletCollisionComponent::CheckHitComponent()
{
}

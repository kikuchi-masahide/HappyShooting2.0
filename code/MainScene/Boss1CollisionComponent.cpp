#include "Boss1CollisionComponent.h"

#include "Boss1MediatorComponent.h"
#include "../Engine/GameObject.h"
#include "DrawBoss1Component.h"
#include "CollisionUIScreen.h"

Boss1CollisionComponent::Boss1CollisionComponent(GameObjectHandle handle, boost::shared_ptr<CollisionManager> manager, boost::shared_ptr<ScoreManager> score_manager, ComponentHandle<Boss1MediatorComponent> mediator)
	:EnemyBodyCollisionComponent<Boss1MediatorComponent>(handle,manager,score_manager,mediator,200,200),
	mediator_(mediator)
{
	for (int n = 0; n < 4; n++)
	{
		polygon_[n] = PolygonGeometry(This<CollisionComponent>(), 4);
	}
	SetPolygonCoord();
	for (int n = 0; n < 4; n++)
	{
		manager->collision_ui_->AddPolygonGeometry(&(polygon_[n]),MatVec::Vector3(0.5,0.0,0.0));
	}
}

Boss1CollisionComponent::~Boss1CollisionComponent()
{
	for (int n = 0; n < 4; n++)
	{
		manager_->collision_ui_->DeletePolygonGeometry(&(polygon_[n]));
	}
}

void Boss1CollisionComponent::Update()
{
	if (mediator_->IsCollisionActive())
	{
		SetPolygonCoord();
		for (int n = 0; n < 4; n++) {
			manager_->AddEnemyGeometry(&(polygon_[n]));
		}
	}
}

void Boss1CollisionComponent::SetPolygonCoord()
{
	double deg = mediator_->GetSquareGrad();
	double dist = mediator_->GetSquareCenterDist();
	auto obj_pos = mediator_->mObj->GetPosition();
	double width = DrawBoss1Component::square_w_;
	for (int i = 0; i < 4; i++)
	{
		polygon_[0].points_[i] = MatVec::Vector2(cos(deg), sin(deg)) * dist + MatVec::Vector2(cos(deg + PI * (2 * i + 1) / 4), sin(deg + PI * (2 * i + 1) / 4))*width/sqrt(2);
	}
	for (int n = 1; n < 4; n++)
	{
		for (int i = 0; i < 4; i++)
		{
			polygon_[n].points_[i] = MatVec::Vector2(-polygon_[n - 1].points_[i](1), polygon_[n - 1].points_[i](0));
		}
	}
	for (int n = 0; n < 4; n++)
	{
		for (int i = 0; i < 4; i++)
		{
			polygon_[n].points_[i] += obj_pos;
		}
	}
}

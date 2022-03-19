#include "Enemy8CollisionComponent.h"

Enemy8CollisionComponent::Enemy8CollisionComponent(GameObjectHandle object, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<ScoreManager> score_manager, ComponentHandle<EnemyHealthComponent> health_component)
	:EnemyBodyCollisionComponent(object,collision_manager,score_manager,health_component,100),
	is_valid_(false)
{
	poly_[0] = PolygonGeometry(This<CollisionComponent>(), 3);
	poly_[1] = PolygonGeometry(This<CollisionComponent>(), 3);
}

Enemy8CollisionComponent::~Enemy8CollisionComponent()
{
}

void Enemy8CollisionComponent::Update()
{
	if (!is_valid_)
	{
		return;
	}
	auto mypos = mObj->GetPosition();
	for (int t = 0; t < 2; t++)
	{
		for (int v = 0; v < 3; v++)
		{
			poly_[t].points_[v] = poly_temp[t][v] + mypos;
		}
		manager_->AddEnemyGeometry(&(poly_[t]));
	}
}

MatVec::Vector2 Enemy8CollisionComponent::poly_temp[2][3] = {
	{
		MatVec::Vector2(cos(PI/6),sin(PI/6))*30,
		MatVec::Vector2(cos(PI*5/6),sin(PI*5/6))*30,
		MatVec::Vector2(cos(PI*2/3),sin(PI*2/3))*30
	},{
		MatVec::Vector2(cos(PI / 2),sin(PI / 2)) * 30,
		MatVec::Vector2(cos(PI*7/6),sin(PI*7/6))*30,
		MatVec::Vector2(cos(PI*11/6),sin(PI*11/6))*30
	}
};

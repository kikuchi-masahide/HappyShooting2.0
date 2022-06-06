#include "Enemy6CollisionComponent.h"

#include "../Engine/GameObject.h"

Enemy6CollisionComponent::Enemy6CollisionComponent(GameObjectHandle object, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<ScoreManager> score_manager, ComponentHandle<EnemyHealthComponent> health_component, int time)
	:EnemyBodyCollisionComponent(object, collision_manager, score_manager, health_component, 100),
	time_(time), polygon_(This<CollisionComponent>(), 4)
{
}

Enemy6CollisionComponent::~Enemy6CollisionComponent()
{
}

void Enemy6CollisionComponent::Update()
{
	//“–‚½‚è”»’è‚ðA(x+w,y)(x,y+h),(x-w,y),(x,y-h)‚ð’Ê‚é‚Ð‚µŒ`‚Å‹ßŽ—‚·‚é
	double w = (3 + sin(PI * time_ / 60)) * 10;
	double h = 60 - w;
	double x = mObj->GetPosition()(0);
	double y = mObj->GetPosition()(1);
	polygon_.points_[0] = MatVec::Vector2(x + w, y - 0);
	polygon_.points_[1] = MatVec::Vector2(x + 0, y + h);
	polygon_.points_[2] = MatVec::Vector2(x - w, y + 0);
	polygon_.points_[3] = MatVec::Vector2(x - 0, y - h);
	manager_->AddEnemyGeometry(&polygon_);
	time_++;
}

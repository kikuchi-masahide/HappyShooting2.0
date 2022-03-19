#pragma once
#include "EnemyBodyCollisionComponent.h"

#include "EnemyHealthComponent.h"
#include "PolygonGeometry.h"

class Enemy8CollisionComponent :
    public EnemyBodyCollisionComponent<EnemyHealthComponent>
{
public:
    Enemy8CollisionComponent(GameObjectHandle object, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<ScoreManager> score_manager, ComponentHandle <EnemyHealthComponent> health_component);
    ~Enemy8CollisionComponent();
    void Update() override;
    //�����蔻���L�������邩�ۂ�(Mediator����ݒ肷��)
    bool is_valid_;
private:
    PolygonGeometry poly_[2];
    //poly_�̒��_�ݒ�̂ЂȌ^ poly_�̊e�_�́Apoly_temp�ɃI�u�W�F�N�g�ʒu�𑫂�������
    static MatVec::Vector2 poly_temp[2][3];
};



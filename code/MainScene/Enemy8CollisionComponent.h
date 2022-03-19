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
    //当たり判定を有効化するか否か(Mediatorから設定する)
    bool is_valid_;
private:
    PolygonGeometry poly_[2];
    //poly_の頂点設定のひな型 poly_の各点は、poly_tempにオブジェクト位置を足したもの
    static MatVec::Vector2 poly_temp[2][3];
};



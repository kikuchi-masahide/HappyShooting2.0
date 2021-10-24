#pragma once
#include "CollisionComponent.h"

class EnemyHealthComponent;
class ScoreManager;

//敵機当たり判定のCheckHitComponent()は共通なので，その共通処理を持つこのクラスをベースにする
class EnemyBodyCollisionComponent :
    public CollisionComponent
{
public:
    EnemyBodyCollisionComponent(GameObjectHandle object, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<ScoreManager> score_manager, ComponentHandle<EnemyHealthComponent> health, unsigned int damage, int upd_priority = 100);
    virtual ~EnemyBodyCollisionComponent();
    virtual void Update() = 0;
    void CheckHitComponent() override;
protected:
    ComponentHandle<EnemyHealthComponent> health_component_;
    boost::shared_ptr<ScoreManager> score_manager_;
};
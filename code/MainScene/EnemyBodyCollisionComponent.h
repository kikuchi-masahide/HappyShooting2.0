#pragma once
#include "CollisionComponent.h"
#include "ScoreManager.h"

//敵機当たり判定のCheckHitComponent()は共通なので，その共通処理を持つこのクラスをベースにする
//敵ヘルス管理を行うクラスも指定する
template<class T>
class EnemyBodyCollisionComponent :
    public CollisionComponent
{
public:
    //health_componentはDamage()を要する
    EnemyBodyCollisionComponent(GameObjectHandle object, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<ScoreManager> score_manager, ComponentHandle<T> health_component, unsigned int damage, int upd_priority = 100)
    : CollisionComponent(object, collision_manager, upd_priority, CollisionManager::Tag::EnemyBody, damage),
        health_component_(health_component), score_manager_(score_manager)
    {
    }
    virtual ~EnemyBodyCollisionComponent()
    {
    }
    virtual void Update() = 0;
    void CheckHitComponent() override
    {
        for (auto comp : hit_comps_)
        {
            //自機または自機弾との衝突
            if (comp->tag_ == CollisionManager::Tag::MyBullet)
            {
                auto damage = comp->GetDamage();
                auto real_damage = health_component_->Damage(damage);
                score_manager_->AddScore(real_damage);
            }
        }
    }
protected:
    ComponentHandle<T> health_component_;
    boost::shared_ptr<ScoreManager> score_manager_;
};
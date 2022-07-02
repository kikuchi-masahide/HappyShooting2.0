#pragma once
#include "CollisionComponent.h"
#include "ScoreManager.h"

//�G�@�����蔻���CheckHitComponent()�͋��ʂȂ̂ŁC���̋��ʏ����������̃N���X���x�[�X�ɂ���
//�G�w���X�Ǘ����s���N���X���w�肷��
template<class T>
class EnemyBodyCollisionComponent :
    public CollisionComponent
{
public:
    //health_component��Damage()��v����
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
            //���@�܂��͎��@�e�Ƃ̏Փ�
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
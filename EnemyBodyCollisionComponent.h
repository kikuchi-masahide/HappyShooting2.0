#pragma once
#include "CollisionComponent.h"

class EnemyHealthComponent;
class ScoreManager;

//�G�@�����蔻���CheckHitComponent()�͋��ʂȂ̂ŁC���̋��ʏ����������̃N���X���x�[�X�ɂ���
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
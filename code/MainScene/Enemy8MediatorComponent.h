#pragma once
#include "../Engine/Component.h"

class LayerManager;
class ScoreManager;
class EnemyWaveManager;
class CollisionManager;
class ScoreManager;
class DrawAnimationComponent;
class Enemy8CollisionComponent;

/// /// <summary>
/// Enemy8�̊e�̂̏������A���W�ύX�A�U���E�s�̐ݒ�A�e�̔��˂��s��
/// </summary>
class Enemy8MediatorComponent :
    public Component
{
public:
    Enemy8MediatorComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col, boost::shared_ptr<ScoreManager> score, GameObjectHandle myself);
    ~Enemy8MediatorComponent();
    void Update() override;
private:
    //���߂�Udpate���Ăяo�����Ƃ�0�Amod120�����
    int time_;
    boost::shared_ptr<LayerManager> layer_;
    GameObjectHandle myself_;
    ComponentHandle<DrawAnimationComponent> animation_;
    ComponentHandle<Enemy8CollisionComponent> col_comp_;
    //������p���āA�����̈ʒu�������_���ɕύX����
    void SetPosition();
};

